/*
六一儿童节,老师带了很多好吃的巧克力到幼儿园。每块巧克力
j 的重量为 w[j],
对于每个小朋友 i,
当他分到的巧克力大小达到 h[i]
(即 w[j]>=h[i]),他才会上去表演节目。老师的目标是将巧克力分
发给孩子们,使得最多的小孩上台表演。可以保证每个 w[i]> 0 且不
能将多块巧克力分给一个孩子或将一块分给多个孩子。(题目来源:
拼多多面试题)

思路：排序，遍历
*/

#include<iostream>
#include<algorithm>
using namespace std;

class solution
{
public:
    void fun()
    {
        int stu,cho;
        cin>>stu;
        int ss[stu];
        for(int i=0;i<stu;i++)
        {
            cin>>ss[i];
        }
        cin>>cho;
        int cc[cho];
        for(int i=0;i<cho;i++)
        {
            cin>>cc[i];
        }
        sort(ss,ss+stu);
        sort(cc,cc+cho);
        int count=0,j=0;
        for(int i=0;i<cho;i++)
        {
            if(cc[i]>=ss[j] && j<stu)  //如果巧克力数比儿童需要巧克力数大，并且还剩有儿童。可以表演，加1
            {
                count++;
                j++;
            }
        }
        cout<<count<<endl;
    }
};

int main()
{
    solution aa;
    aa.fun();
}