/*
牛牛对整除非常感兴趣。牛牛的老师给他布置了一道题:牛牛的
老师给出一个 n,然后牛牛需要回答出能被 1 到 n 之间(包括 1 和 n)
所有整数整除的最小的数。牛牛犯了难,希望你能编程帮他解决这个
问题。

自己方法：从最大开始，往下整除，如果除不尽最大+一倍，但是由于越往上，数越大，所以到后面程序跑不出来
百度方法：找每个
*/


#include<iostream>
#include<algorithm>
using namespace std;

/*因为结果会很大，这样太慢，基本100以上就跑不出来了！！！*/
class solution
{
public:
    int fun()
    {
        long long x;
        cin>>x;
        auto n=x;
        int flag=0;
       
        while(1)
        {
            if(n%2!=0)
            {
                n=n+x;
                continue;
            }
            flag=0;
            for(auto i=x;i>=2;i--)
            {  
                //cout<<"n:"<<n<<" i:"<<i<<" n%i:"<<n%i<<endl;
                if(n%i!=0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                break;
            }
            n=n+x;
            //cout<<n<<endl;
        }
        return n;
    }

};

/* */
class solution1
{
public:
    int fun()
    {
        int n;
        cin>>n;
        int a[n+1];
        for(int i=0;i<=n;i++)
        {
            a[i]=0;
        }
        for(int i=1;i<=n;i++)
        {
            int k=i;
            for(int j=2;j*j<=n;j++)
            {
                int s=0;
                while(k%j==0)
                {
                    s++;
                    k/=j;
                }
                a[j]=max(a[j],s);
               // cout << a[j] << ' ' << j << endl;
            }
            if(k>1)
            {
                a[k]=max(a[k],1);
              // cout << a[k] << '*' << k << endl;
            }
        }
        /*for(int i=0;i<=n;i++)
        {
            cout<<a[i]<<'/'<<endl;
        }*/
        //cout<<'*'<<endl;
        long long int sum=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<a[i];j++)
            {
                sum=sum*i%987654321;
                //cout<<i<<' '<<j<<' '<< a[i]<<' '<<sum<<endl;
            }
        }
        //cout<<sum<<endl;
        return sum;
    }
};

int main()
{
    //solution aa;
    //cout<<aa.fun()<<endl;
     solution1 bb;
    cout<<bb.fun()<<endl;
}