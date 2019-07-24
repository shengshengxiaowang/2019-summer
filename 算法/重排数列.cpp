#include<iostream>
using namespace std;
/*
小易有一个长度为N的正整数数列A = {A[1], A[2], A[3]..., A[N]}。
牛博士给小易出了一个难题:
对数列A进行重新排列,使数列A满足所有的A[i] * A[i + 1](1 ≤ i ≤ N - 1)都是4的倍数。
小易现在需要判断一个数列是否可以重排之后满足牛博士的要求。

非常简单的题，标记4的倍数，2的倍数，还有什么都不是的无倍数都是几个
然后判断即可，4倍数比无倍数多肯定可以，因为将无倍数放在最前面即可，单独的4倍数跟2倍数都可以满足条件，这就包含了两个都没有的情况了
如果只有4倍数和无倍数，并且4倍数比无倍数少1个也是可以的，将无倍数放在开头结尾即可。
*/
class solution
{
public:
    bool fun(int n)
    {
        int a[n];
        int x4=0,x2=0,x=0;
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
            if(a[i]%4==0)
            {
                x4++;
            }
            else if(a[i]%2==0)
            {
                x2++;
            }
            else
            {
                x++;
            }   
        }
        if(x4>=x)//如果4的倍数大于等于无倍数
        {
            return 1;
        }
        if(x4+1==x && x4!=0 && x2==0)//如果4的倍数比无倍数多一个并且其他没了
        {
            return 1;
        }
        return 0;
    }

};


int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int c;
        cin>>c;
        solution aa;
        if(aa.fun(c)==1)
        {
            cout<<"Yes"<<endl;
        }
        else
        {
            cout<<"No"<<endl;
        }
        
        //cout<<boolalpha<<aa.fun(c)<<endl;
    }
}