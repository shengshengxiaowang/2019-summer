#include<iostream>
using namespace std;

/*深搜解法*/
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
    solution aa;
    aa.dfs(1,x,1,2);
    cout<<mins<<endl;
}