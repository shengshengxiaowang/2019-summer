/*
给定一个无序数组,包含正数、负数和 0,要求从中找出 3 个数
的乘积,使得乘积最大,要求时间复杂度:O(n),空间复杂度:O(1)
(题目来源:拼多多面试题)

思路：就是先将排序，再比较，前三个大的，后三个小的，一个大的和两个最小的。
*/

#include<iostream>
#include<algorithm>
using namespace std;

//感觉牛客的测试用例有问题，检查不出来，显示错误，但是显示出来的错误的那个用例数据都不全，也没办法看到底什么是错误
class solution
{
public:
    long long int fun()
    {
        long long int n;
        cin>>n;
        long long int a[n+1];
        for(long long int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        long long int s1,s2,s3,s4,s5,s6;
        sort(a,a+3);
        s1=a[2];
        s2=a[1];
        s3=a[0];
        s4=a[2];
        s5=a[1];
        s6=a[0];
        //cout<<s1<<' '<<s2<<' '<<s3<<' '<<s4<<' '<<s5<<endl;
        for(long long int c=0;c<n;c++)
        {
            if(a[c]>s1)
            {
                s3=s2;
                s2=s1;
                s1=a[c];
            }
            else if(a[c]>s2 && a[c]<s1)
            {
                s3=s2;
                s2=a[c];
            }
            else if(a[c]>s3 && a[c]<s2)
            {
                s3=a[c];
            }
            else if(a[c]<s6)
            {
                s4=s5;
                s5=s6;
                s6=a[c];
            }
            else if(a[c]<s5 && a[c]>s6)
            {
                s4=s5;
                s5=a[c];
            }
            else if(a[c]<s4 && a[c]>s5)
            {
                s4=a[c];
            }     
        }  
        return max(max(s1*s2*s3,s1*s5*s6),s4*s5*s6);
    }
};

//这个通过了
class solution1
{
public:
    long long int fun()
    {
        long long int n;
        cin>>n;
        long long int a[n+1];
        for(long long int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        sort(a,a+n);
        return max(max(a[n-3]*a[n-2]*a[n-1],a[0]*a[1]*a[n-1]),a[0]*a[1]*a[2]);
    }
};

int main()
{
    solution aa;
    cout<<aa.fun()<<endl;

}

