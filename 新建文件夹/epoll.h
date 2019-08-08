#ifndef EPOLL_H
#define EPOLL_H

#include <iostream>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string>
#include <memory.h>
#include <fcntl.h>
#include "http.h"

using namespace std;

#define MAXSIZE 2000

class epoll
{
  public:
    epoll(int a);
    ~epoll();

  public:
    void epoll_run();
    int init_listen_fd(int epfd);
    void do_accept(int llfd);

  private:
    int port;
    int epfd; //epoll树根节点
    //int lfd;  //监听节点
};

inline void epoll::epoll_run()
{

    epfd = epoll_create(MAXSIZE); //初始化epoll树根节点
    if (epfd == -1)
    {
        perror("epoll树根节点 error");
        exit(1);
    }
    // 添加要监听的节点
    // 先添加监听lfd
    
    int lfd = init_listen_fd(epfd);
    // 委托内核检测添加到树上的节点
    struct epoll_event all[MAXSIZE];

    while (1)
    { 
        int ret=epoll_wait(epfd, all, MAXSIZE, -1);
        if (ret==-1)
        {
            perror("epoll_wait error");
            exit(1);
        }

        // 遍历发生变化的节点
        for (int i = 0; i < ret; ++i)
        {
            // 只处理读事件, 其他事件默认不处理
            struct epoll_event *pev = &all[i];
            if (!(pev->events & EPOLLIN)) // 不是读事件
            {
                continue;
            }
            if (pev->data.fd == lfd)
            {
                do_accept(lfd); // 接受连接请求
            }
            else
            {
                http my_http(pev->data.fd,epfd);
                //do_read(pev->data.fd, epfd);// 读数据
            }
        }
    }
    cout << port << endl;
}

inline void epoll::do_accept(int llfd) // 接受新连接处理函数
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int cfd = accept(llfd, (struct sockaddr *)&client, &len);
    if (cfd == -1)
    {
        perror("accept error");
        exit(1);
    }
    // 打印客户端信息
    char ip[64] = {0};
    cout << "New Client IP: " << inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof(ip)) << endl;
    cout << "Port:" << ntohs(client.sin_port) << endl;
    cout << "cfd =" << cfd << endl;

    // 设置cfd为非阻塞
    int flag = fcntl(cfd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(cfd, F_SETFL, flag);

    // 得到的新节点挂到epoll树上
    struct epoll_event ev;
    ev.data.fd = cfd;

    // 边沿非阻塞模式
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
    if (ret == -1)
    {
        perror("epoll_ctl add cfd error");
        exit(1);
    }
}

inline int epoll::init_listen_fd(int epfd) //监听函数
{
    int llfd = socket(AF_INET, SOCK_STREAM, 0);
    //cout<<"llfd:"<<llfd<<endl;
    if (llfd == -1)
    {
        perror("socket error");
        exit(1);
    }
    // llfd绑定本地IP和port
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    // 端口复用
    int flag = 1;
    setsockopt(llfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    int ret = bind(llfd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret == -1)
    {
        perror("bind error");
        exit(1);
    }

    // 设置监听
    ret = listen(llfd, 64);
    if (ret == -1)
    {
        perror("listen error");
        exit(1);
    }

    // lfd添加到epoll树上
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = llfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, llfd, &ev);
    if (ret == -1)
    {
        perror("epoll_ctl add llfd error");
        exit(1);
    }
    //cout<<"ret:"<<ret<<endl;
    return llfd;
}

inline epoll::epoll(int a)
{
    port = a;
    cout << port << endl;
    epoll_run();
}
inline epoll::~epoll()
{
}

#endif