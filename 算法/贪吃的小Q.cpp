
/*
小 Q 的父母要出差 N 天,走之前给小 Q 留下了 M 块巧克力。小 Q
决定每天吃的巧克力数量不少于前一天吃的一半,但是他又不想在父
母回来之前的某一天没有巧克力吃,请问他第一天最多能吃多少块巧
克力?(题目来源:腾讯面试题)
输入描述:
每个输入包含一个测试用例。
每个测试用例的第一行包含两个正整数,表示父母出差的天数
N(N<=50000)和巧克力的数量 M(N<=M<=100000)。
输出描述:
输出一个数表示小 Q 第一天最多能吃多少块巧克力。
示例:
输入:
3 7
输出:
4
*/
//思路：二分法缩边界，边界设定必须要仔细，还要考虑没有刚合适的情况（我看大佬的代码是直接走的高边界，不懂emmmm）



#include<iostream>

using namespace std;

class solution
{
public:
    int fun(int c,int n)
    {
        if(c==1)  //不要也可以
        {
            return n;
        }
        int sta,end,mid;
        sta=1;end=n;
        while(sta<end && sta+1!=end)  //如果中间没有范围了退出
        {
            mid=(sta+end)/2;
            //cout<<sta<<mid<<end<<endl;
            int i=index(mid,c);
            if(i==n)
            {
                return mid;
            }
            else if(i>n)
            {
                end=mid-1;//大了肯定不可以，所以可以缩边界，小了的不能缩，可能没有合适的还要用
            }
            else
            {
                sta=mid;
            }
            //cout<<sta<<mid<<end<<endl;
        }
        if(index(end,c)<=n)//没有刚好合适的值，在边界里找值，先看大的，如果超出就是小的
        {
             return end;
        }
        return sta;     
    }
    int index(int first,int c)
    {
        int sum=0;
        for(int i=0;i<c;i++)
        {
            sum=sum+first;
            first=(first+1)/2;
        }
        return sum;
    } 

};

int main()
{
    int n,c;
    cin>>c>>n;
    solution a;
    cout<<a.fun(c,n)<<endl;
    return 0;
}