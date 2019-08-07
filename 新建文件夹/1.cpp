#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include "epoll.h"

using namespace std;

int main(int argc, char * argv[])
{
	if(argc != 3)  //检测
	{
		cout<<"请输入端口号和当前目录"<<endl;
		exit(1);
	}
    int port=atoi(argv[1]); //将端口号转换为整数存入port
    int ret=chdir(argv[2]);  //改变当前工作目录
    if (ret==-1 || port<100)  //查错
    {
        cout<<"输入错误"<<endl;
        exit(1);
    }
    epoll my_epoll(port); //启动epoll
    

}