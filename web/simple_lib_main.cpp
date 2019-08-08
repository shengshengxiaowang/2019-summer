#include<iostream>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<event2/bufferevent.h>
#include<event2/listener.h>
#include<event2/event.h>

#include "simple_lib.h"
using namespace std;



int main(int argc,char **argv)
{
    if(argc<3)  //判断输入
    {
        cout<<"输入错误"<<endl;
        return -1;
    }
    if(chdir(argv[2])<0)  //切换目录、判断
    {
        cout<<"目录错误"<<endl;
        return -1;
    }
    struct event_base *base;  //构造event_base
    struct evconnlisten *listener; 
    struct event *signal_event;
    struct sockaddr_in sin;
    base=event_base_new();
    if(!base)
    {
        //fprintf(stderr,"libevent初始化错误\n");
        cout<<"base:error"<<endl;
        return 1;
    }
    memset(&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_port=htons(atoi(argv[1]));
    // 创建监听的套接字，绑定，监听，接受连接请求
    //回调函数listener_cb
    listener=evconnlistener_new_bind(base,listener_cb,(void *)base,LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,-1,(struct sockaddr*)&sin,sizeof(sin));
    if (!listener)
    {
        cout<<"singal error"<<endl;
        //fprintf(stderr, "Could not create a listener!\n");
        return 1;
    }
    // 创建信号事件, 捕捉并处理
    signal_event=evsignal_new(base, SIGINT, signal_cb, (void *)base);
    if(!signal_event || event_add(signal_event,NULL)<0) 
    {
        //fprintf(stderr,"Could not create/add a signal event!\n");
        cout<<"singal error"<<endl;
        return 1;
    }
   
    //事件循环
    event_base_dispatch(base);
    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);
    return 0;

}
