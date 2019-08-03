/*
有n只小熊，他们有着各不相同的战斗力。每次他们吃糖时，会按照战斗力来排，战斗力高的小熊拥有优先选择权。前面的小熊吃饱了，后面的小熊才能吃。每只小熊有一个饥饿值，每次进食的时候，小熊们会选择最大的能填饱自己当前饥饿值的那颗糖来吃，可能吃完没饱会重复上述过程，但不会选择吃撑。
现在给出n只小熊的战斗力和饥饿值，并且给出m颗糖能填饱的饥饿值。
求所有小熊进食完之后，每只小熊剩余的饥饿值。



输入描述:
第一行两个正整数n和m，分别表示小熊数量和糖的数量。（n <= 10, m <= 100）
第二行m个正整数，每个表示着颗糖能填充的饥饿值。
接下来的n行，每行2个正整数，分别代表每只小熊的战斗力和当前饥饿值。
题目中所有输入的数值小于等于100。


输出描述:
输出n行，每行一个整数，代表每只小熊剩余的饥饿值。

思路：排序，依次选择，很简单的题
*/

#include<iostream>
#include<algorithm>
using namespace std;

struct bearr
{
    int i,fight,hunger;
};

class solution
{
public:
    static bool cmp(bearr a,bearr b)  //bear结构体排序
    {
        return a.fight>b.fight;
    }
    static bool cmd(int a,int b)   //sweet数组排序
    {
        return a>b;
    }
    static bool cmk(bearr a,bearr b)  //bear恢复数组顺序
    {
        return a.i<b.i;
    }
    
    void fun()
    {
        int bearn,sweetn;
        cin>>bearn>>sweetn;
        int sweet[sweetn];
        for(int i=0;i<sweetn;i++)
        {
            cin>>sweet[i];
        }
        bearr bear[bearn];  //bear结构体
        
        for(int i=0;i<bearn;i++)
        {
            cin>>bear[i].fight;
            cin>>bear[i].hunger;
            bear[i].i=i;
        }
        sort(bear,bear+bearn,cmp);
        sort(sweet,sweet+sweetn,cmd);
        
       /* for(int i=0;i<sweetn;i++)
        {
            cout<<sweet[i]<<' ';
        }
        cout<<endl;*/
       
        for(int i=0;i<bearn;i++)
        {
            for(int j=0;j<sweetn;j++)
            {
                if(sweet[j]==0)
                {
                    continue;
                }
                if((bear[i].hunger-sweet[j])>=0) //如果当前饥饿值可以吃这个糖
                {
                    //cout<<sweet[j]<<' '<<bear[i].i<<' ';
                    bear[i].hunger-=sweet[j];
                    sweet[j]=0;    //标记糖果值为0
                    if(bear[i].hunger==0)  //如果刚好吃饱,退出循环
                    {
                        break;
                    }
                }
            }
            //cout<<endl;
        }
        sort(bear,bear+bearn,cmk);
        for(int i=0;i<bearn;i++)
        {
            cout<<bear[i].hunger<<endl;
        }
    }
};
int main()
{
    solution aa ;
    aa.fun();
}



/*6 60
43 24 72 84 44 96 58 36 67 39 1 28 50 57 31 13 66 76 96 10 16 31 17 61 80 6 36 45 33 75 89 56 74 66 92 10 69 43 19 76 78 18 82 39 49 4 89 37 12 83 53 31 29 25 73 94 2 19 43 77
70 59
28 56
43 21
23 57
89 59
12 2*/