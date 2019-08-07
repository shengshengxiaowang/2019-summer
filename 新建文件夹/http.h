#ifndef HTTP_h
#define HTTP_h
#include<iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include<stdio.h>
#include<ctype.h>
#include <sys/stat.h>
using namespace std;

class http
{
public:
    http(int ccfd,int eepfd);
    ~http();
public:
    int get_line(char *buf,int size);
    void disconnect();
    void http_request(const char* request);
    void decode_str(char *to, char *from);
    int hexit(char c);
    void send_respond_head(int no,const char* desp,const char* type,long len);
    void send_file(const char* filename);
private:
    int cfd;
    int epfd;
};

inline http::http(int ccfd,int eepfd)
{
    cfd=ccfd;//初始化
    epfd=eepfd;
    // 将浏览器发过来的数据, 读到buf中 
    char line[1024] = {0};
    //cout<<"http*:"<<cfd<<"*"<<epfd<<endl;
    // 读请求行
    int len=get_line(line, sizeof(line));
    //cout<<"len:"<<len<<endl;
    if(len==0)
    {
        cout<<"客户端断开了连接..."<<endl;
        disconnect();    // 关闭套接字, cfd从epoll上del      
    }
    else
    {
        cout<<"请求行数据:"<<line<<endl;
        cout<<"----请求头----"<<endl;
        while(len) // 还有数据没读完,继续读
        {
            char buf[1024] = {0};
            len = get_line(buf, sizeof(buf));
            cout<<buf<<endl;
        }
        cout<<"----读取完毕----"<<endl;
    }
    if(strncasecmp("get",line,3)==0) //判断是不是get请求
    {
        http_request(line); //处理http请求

    }

}

inline void http::http_request(const char* request)// http请求处理
{
    char method[12], path[1024], protocol[12]; //拆分http请求行
    sscanf(request, "%[^ ] %[^ ] %[^ ]", method, path, protocol);
    cout<<"method = "<<method<<endl;
    cout<<"path = "<<path<<endl;
    cout<<"protocol = "<<protocol<<endl;
   
    decode_str(path, path); // 解码 16进制
    const char* file = path+1;
    if(strcmp(path,"/")==0) //如果没有指定访问的资源, 默认显示资源目录中的内容
    {
        file="./"; //资源目录的当前位置
    }

    struct stat st; // 获取文件属性
    int ret=stat(file,&st);
    if(ret==-1)  //展示 404页面
    {
        send_respond_head(404, "File Not Found", ".html", -1);
        send_file("404.html");
    }
    // 判断是目录还是文件
    // 如果是目录



//写到这里了




}

// 发送文件
inline void http::send_file(const char* filename)
{
    int fd=open(filename, O_RDONLY);
    if(fd==-1)
    {
        return;
    }
    // 循环读文件
    char buf[4096]={0};
    int len=0;
    while( (len=read(fd,buf,sizeof(buf))) >0)
    {
        send(cfd, buf, len, 0);  //发送读出的数据
    }
    if(len==-1)
    {
        perror("read file error");
        exit(1);
    }
    close(fd);
}

// 发送响应头
inline
void http::send_respond_head(int no,const char* desp,const char* type,long len)
{
    char buf[1024]={0};
    sprintf(buf,"http/1.1 %d %s\r\n",no,desp);// 状态行
    send(cfd,buf,strlen(buf),0);
    sprintf(buf,"Content-Type:%s\r\n",type);  // 消息报头
    sprintf(buf+strlen(buf), "Content-Length:%ld\r\n", len);
    send(cfd, buf, strlen(buf), 0);
    send(cfd, "\r\n", 2, 0); // 空行
}

inline void http::decode_str(char *to, char *from) //解码 16进制
{
    for( ;*from!='\0';++to,++from) 
    {
        if(from[0]=='%' && isxdigit(from[1]) && isxdigit(from[2])) //检测16进制
        { 
            *to=hexit(from[1])*16+hexit(from[2]);
            from+=2;                      
        } 
        else
        {
            *to=*from;
        }
    }
    *to='\0';
}

inline int http::hexit(char c)  //16进制数转化为10进制
{
    if(c>='0' && c<='9')
        return (c-'0');
    if (c>='a' && c<='f')
        return (c-'a'+10);
    if (c>='A' && c<='F')
        return (c-'A'+10);
    return 0;
}


inline void http::disconnect() //断开连接函数
{
    int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,NULL);
    if(ret==-1)
    {
        perror("epoll_ctl del cfd error");
        exit(1);
    }
    close(cfd);
}

inline 
int http::get_line(char *buf,int size)//// 解析http请求消息的每一行内容函数
{
    int i=0;
    char c='\0';
    int n;
    while( (i<size-1) && (c!='\n'))
    {
        n=recv(cfd,&c,1,0);
        if(n>0)
        {
            if(c=='\r')
            {
                n=recv(cfd,&c,1,MSG_PEEK);
                if( (n>0) && (c=='\n'))
                {
                    recv(cfd,&c,1,0);
                }
                else
                {
                    c='\n';
                }
            }
            buf[i]=c;
            i++;
        }
        else
        {
            c='\n';
        }
    }
    buf[i]='\0';
    return i;
}

inline http::~http()
{

}

#endif