/*牛牛和羊羊正在玩一个纸牌游戏。这个游戏一共有 n 张纸牌, 第
i 张纸牌上写着数字 ai。
牛牛和羊羊轮流抽牌, 牛牛先抽, 每次抽牌他们可以从纸牌堆中任
意选择一张抽出, 直到纸牌被抽完。
他们的得分等于他们抽到的纸牌数字总和。
现在假设牛牛和羊羊都采用最优策略, 请你计算出游戏结束后牛牛
得分减去羊羊得分等于多少。 (题目来源:腾讯面试题)
输入描述:
输入包括两行。
第一行包括一个正整数 n(1 <= n <= 105),表示纸牌的数量。
第二行包括 n 个正整数 ai(1 <= ai <= 109),表示每张纸牌上的数字。
输出描述:
输出一个整数, 表示游戏结束后牛牛得分减去羊羊得分等于多少。
示例:
输入:
3
2 7 4
输出:
5*/
//思路：排序，依次减就行
#include<iostream>
#include<algorithm>
using namespace std;

class solution
{
public:
    int fun(int n,int *s)
    {
        sort(s,s+n);
        int sum=0;
        for(int i=n-1;i>=1; )
        {
            sum=sum+s[i]-s[i-1];
            i-=2;
            //cout<<i<<endl;
        }
        if(n%2==1)
        {
            sum+=s[0];
        }
        return sum;
    } 

};

int main()
{
    int n;
    cin>>n;
    int s[n];
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
    }
    solution a;
    cout<<a.fun(n,s)<<endl;
}