/*
小招喵喜欢在数轴上跑来跑去，假设它现在站在点n处，它只会3种走法，分别是：
1.数轴上向前走一步，即n=n+1 
2.数轴上向后走一步,即n=n-1 
3.数轴上使劲跳跃到当前点的两倍，即n=2*n
现在小招喵在原点，即n=0，它想去点x处，快帮小招喵算算最快的走法需要多少步？
*/


#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*动态规划解法：
对于动态规划，我一直都不是很熟悉，所以这个的动态规划解法，我是照着大佬的看懂然后写的，动态规划看懂了不难，但是下一道题还是不会emmmm
慢慢做吧，希望多做我可以会。
这个的动态规划解法主要是，因为*2肯定会更快，所以如果是偶数，就要看是通过乘2来的还是+1来的
如果是奇数，就要看是加1来的还是一个数乘2再减1来的 
因为是通过一步一步计算最优解，所以只有之前的值*/
class solution1
{
public:
    int min(int a,int b)
    {
        if(a>b)
            return b;
        return a;
    }
    int fun(int x)
    {
        /*if(x<0)
        {
            x=-x;
        }*/
        int dp[x+1];
        
        dp[0]=0;
        dp[1]=1;
        for(int i=2;i<=x;i++)
        {
            if(i%2==0) //偶数是从除2乘来,或者之前一个数加1来的
            {
                dp[i]=min(dp[i/2],dp[i-1])+1;
            }
            else   //如果是奇数，那么是从之前一个数加1或者由一个数乘2再减1，两步，所以要加1
            {
                dp[i]=min(dp[i-1],dp[(i+1)/2]+1)+1;
            }
            
        }
        return dp[x];
    }

};


/*深搜解法：
普通深搜，但是因为可以先减后加或者先加后减容易死循环，所以需要仔细注意加一堆限制条件
尤其是当前步数已经大于最小步数则直接退出这个条件，我会经常容易忘，但是测试的时候，不加这个，数如果一大的话还是会循环跑不出来
*/
int mins=999;
class solution
{
public:
    void dfs(int n,int x,int step,int back)
    {
        //cout<<n<<' '<<x<<' '<<step<<' '<<endl;
        if(x<0)  //如果是负数
        {
            x=-x;
        }
        if(x==0)    //如果为0
        {
            mins=0;
            return ;
        }
        if(n==x) //如果到了x点退出
        {
            //cout<<step<<mins<<endl;
            if(step<mins)
            {
                mins=step;
            }
            return;
        }
        if(n>=2*x || n<=0 || step>mins)  //如果大于x的2倍 或者小于等于0回到了原点 或者当前步数大于已知最小步数
        {
            return;
        }     

        if(n<x)  //如果n比x小才可以*2和++
        {
            dfs(n*2,x,step+1,1);
            if(back!=3)  //如果上一步是--，则不要++
            {
                dfs(n+1,x,step+1,2);
            }
            
        }
        if(n>2 && back!=2)  //不回到原点并且上一步不是++
        {
            dfs(n-1,x,step+1,3);
        }  
        
        return;
    }
    
};
int main()
{
    int x;
    cin>>x;

    solution aa;//递归解法
    aa.dfs(1,x,1,2);
    cout<<mins<<endl;

    solution1 bb;//动态规划解法
    cout<<bb.fun(abs(x))<<endl;
}