//大数相乘
#include<iostream>
#include<string.h>
using namespace std;
#define N 200

class solution
{
public:
    void fun()
    {
        char a[N];
        char b[N];
        unsigned char s[N];
        for(int i=0;i<N;i++)
        {
            s[i]=0;
        }
        cin>>a;
        cin>>b;
        int count=1,k;
        int la=strlen(a),lb=strlen(b);
        for(int i=lb-1;i>=0;i--)
        {
            k=N-count;
            for(int j=la-1;j>=0;j--)
            {
                s[k]=s[k]+((b[i]-48)*(a[j]-48));
                k--;
            }
            for(int l=N-count++;l>k-2;l--)
            {
                if(s[l]<10)
                {
                    continue;
                }
                int m,n;
                n=s[l];
                s[l]=n%10;
                m=n/10;
                s[l-1]=s[l-1]+m;
            }  
        }
        cout<<"相乘结果："<<endl;
        for(int i=0;i<N;i++)
        {
            if(s[i]!=0)
            {
                for(int j=i;j<N;j++)
                {
                    printf("%d",s[j]);
                }
                cout<<endl;
                break;
            }      
        }
    }
};

class solution1
{
public:
    void fun()
    {
        char a[N];
        char b[N];
        char s[N];
        for(int i=0;i<N;i++) //初始化，为之后判断从哪儿开始输出
        {
            s[i]=0;
        }
        cin>>a;
        cin>>b;
        int la=strlen(a)-1,lb=strlen(b)-1;
        int k=N-1;
        //cout<<la<<lb<<endl;
        while(la>=0 && lb>=0)
        {
            
                s[k]=s[k]+(b[lb--]-48)+(a[la--]-48);
                if(s[k]>=10)
                {
                    s[k]=s[k]%10;
                    s[k-1]++;
                }
                //printf("%d\n",s[k]);
                k--;
            
        }
        if(la>=0 || lb>=0)
        {
            int x=max(la,lb);
            //printf(":%d %d\n",s[k],k);
            for(int i=x;i>=0;i--)
            {
                if(la>=0)
                {
                    s[k]=s[k]+(a[i]-48);
                    //printf("888:%d\n",a[i]);
                    la--;
                }
                else
                {
                    s[k]=s[k]+(b[i]-48);
                    //printf("999:%d\n",b[i]);
                    lb--;
                }
                 //printf(":%d\n",s[k]);
                if(s[k]>=10)
                {
                    s[k]=s[k]%10;
                    s[k-1]++;
                }
                k--; 
                
                
            }
            
        }
        cout<<"相加结果："<<endl;
        for(int i=1;i<N;i++) //输出
        {
            if(s[i]!=0)
            {
                for(int j=i;j<N;j++)
                {
                    printf("%d",s[j]);
                }
                cout<<endl;
                break;
            }      
        }
    }
};
int main()
{
    cout<<endl;
    solution aa;
    aa.fun();
    cout<<endl;
}



