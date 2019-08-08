#include<iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>

using namespace std;

#define _HTTP_CLOSE_ "Connection: close\r\n"

int response_http(struct bufferevent *bev,const char *method,char *path)
{
    if(strcasecmp("GET",method)==0)  //get方法
    {
        strdecode(path,path);
        char *pf=&path[1];
        if(strcmp(path,"/")==0 || strcmp(path,"/.")==0)
        {
            pf="./";
        }
        cout<<"HTTP请求资源路径："<<path<<" "<<pf<<endl;
        struct stat sb;
        if(stat(pf,&sb)<0)
        {
            perror("open file err:");
            send_error(bev);
            return -1;
        }
        if(S_ISREG(sb.st_mode))//如果是文件
        {
            send_header(bev, 200, "OK", get_file_type(pf), sb.st_size);
            send_file_to_http(pf, bev);
        }
    }
    return 0;
}



//通信的文件描述符
void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,struct sockaddr *sa, int socklen, void *user_data)
{
    //cout<<"listen开始："<<__FUNCTION__<<endl;
    struct event_base *base=user_data;
    struct bufferevent *bev;
    cout<<"fd: "<<fd<<endl;
    bev=bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
    if(!bev)
    {
        cout<<"bev error"<<endl;
        event_base_loopbreak(base);
        return;
    }
    bufferevent_flush(bev,EV_READ | EV_WRITE,BEV_NORMAL);
    bufferevent_setcb(bev,conn_readcb,NULL,conn_eventcb,NULL);
    bufferevent_enable(bev,EV_READ | EV_WRITE);
    //cout<<"listen结束："<<__FUNCTION__<<endl;
}

int send_file_to_http(const char *filename,struct bufferevent *bev)
{
    int fd=open(filename,O_RDONLY);
    int ret=0;
    char buf[4096]={0};
    while( (ret=read(fd,buf,sizeof(buf)) ) )
    {
        bufferevent_write(bev,buf,ret);
        memset(buf,0,ret);
    }
    close(fd);
    return 0;
}

const char *http:get_file_type(const char *name)  //通过文件名获取文件的类型函数
{
    const char* dot;
    dot=strrchr(name,'.');   //查找‘.’字符, 如不存在返回NULL
    if(dot==NULL)
        return "text/plain; charset=utf-8";
    if(strcmp(dot,".html")==0 || strcmp(dot,".htm")==0)
        return "text/html; charset=utf-8";
    if(strcmp(dot,".jpg")==0 || strcmp(dot,".jpeg")==0)
        return "image/jpeg";
    if(strcmp(dot,".gif")==0)
        return "image/gif";
    if(strcmp(dot,".png")==0)
        return "image/png";
    if (strcmp(dot,".mp3")==0)
        return "audio/mpeg";
    return "text/plain; charset=utf-8";
}

int send_header(struct bufferevent *bev,int no,const char* desp,const char *type,long len)
{
    char buf[256]={0};
    sprintf(buf,"HTTP/1.1 %d %s\r\n",no,desp);
    //HTTP/1.1 200 OK\r\n
    bufferevent_write(bev,buf,strlen(buf));
    // 文件类型
    sprintf(buf,"Content-Type:%s\r\n",type);
    bufferevent_write(bev,buf,strlen(buf));
    // 文件大小
    sprintf(buf,"Content-Length:%ld\r\n",len);
    bufferevent_write(bev,buf,strlen(buf));
    // Connection: close
    bufferevent_write(bev,_HTTP_CLOSE_,strlen(_HTTP_CLOSE_));
    //send \r\n
    bufferevent_write(bev,"\r\n",2);
    return 0;
}

int send_error(struct bufferevent *bev)
{
    send_header(bev,404,"File Not Found","text/html",-1);
    send_file_to_http("404.html",bev);
    return 0;
}

void conn_readcb(struct bufferevent *bev, void *user_data)
{
    //cout<<"conn_rea开始："<<__FUNCTION__<<endl;
    char buf[4096]={0};
    char method[50],path[4096],protocol[32];
    bufferevent_read(bev,buf,sizeof(buf));
    printf("buf[%s]\n",buf);
    sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",method,path,protocol);
    printf("method[%s],path[%s],protocol[%s]\n",method,path,protocol);
    if(strcasecmp(method,"GET")==0)
    {
        response_http(bev,method,path);
    }
    //cout<<"conn_rea结束："<<__FUNCTION__<<endl;
    
}

void conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
    //cout<<"connect开始："<<__FUNCTION__<<endl;
    if (events & BEV_EVENT_EOF)
    {
        printf("Connection closed.\n");
    }
    else if (events & BEV_EVENT_ERROR)
    {
        printf("Got an error on the connection: %s\n",
               strerror(errno));
    }

    bufferevent_free(bev);
    //cout<<"connect结束："<<__FUNCTION__<<endl
}


void signal_cb(evutil_socket_t sig,short events,void *user_data)
{
    struct event_base *base=user_data;
    struct timeval delay={1,0};
    cout<<"捕捉到一个中断信号"<<endl;
    event_base_loopexit(base,&delay);
}

void strdecode(char *to,char *from)    //解码
{
    for( ;*from!='\0';++to,++from)
    {
         // 依次判断from中 %20 三个字符
        if(from[0]=='%' && isxdigit(from[1]) && isxdigit(from[2]))
        {
            *to=hexit(from[1])*16+hexit(from[2]);
            // 移过已经处理的两个字符(%21指针指向1),表达式3的++from还会再向后移一个字符
            from+=2;
        }
        else
        {
            *to=*from;
        }
    }
    *to='\0';
}


int hexit(char c)  //16进制数转化为10进制函数
{
    if(c>='0'&& c<='9')
        return (c-'0');
    if(c>='a' && c<='f')
        return (c-'a'+10);
    if(c>='A' && c<='F')
        return (c-'A'+10);

    return 0;
}

void strencode(char* to,size_t tosize,const char* from) //编码函数
{
    int tolen;
    for(tolen=0;*from!='\0' && tolen+4<tosize;++from)
    {
        if(isalnum(*from) || strchr("/_.-~",*from)!=(char*)0)
        {
            *to=*from;
            ++to;
            ++tolen;
        }
        else
        {
            sprintf(to,"%%%02x",(int)*from & 0xff);
            to+=3;
            tolen+=3;
        }
    }
    *to='\0';
}