/*
牛牛有两个字符串A和B,其中A串是一个01串,B串中除了可能有0和1,还可能有'?',B中的'?'可以确定为0或者1。
寻找一个字符串T是否在字符串S中出现的过程,称为字符串匹配。牛牛现在考虑所有可能的字符串B,有多少种可以在字符串A中完成匹配。
例如:A = "00010001", B = "??"
字符串B可能的字符串是"00","01","10","11",只有"11"没有出现在字符串A中,所以输出3

先在循环1中用substr函数依次从字符串a中剪切下，长度为b字符串长度的字符串
在循环2中将剪切下来的字符串跟b进行比较
如果相同，进入循3，检测存储的已经成功匹配的字符串中有没有重复的
如果没有，将该剪切下的字符串加入容器中，并且数量加1
*/


#include<iostream>
#include<vector>
#include<string>
using namespace std;

class solution
{
public:
    void fun()
    {
        cin>>a;
        cin>>b;
        int la=a.length();
        int lb=b.length();
        //cout<<la<<lb<<endl;
        int count=0;
        for(int i=0;i<la-lb+1;i++)
        {
            int flag=0;
            string cut=a.substr(i,lb); //截取和b字符串相等的字符串
            //cout<<cut<<endl;
            for(int j=0;j<lb;j++)
            {
                //cout<<cut[0]<<' '<<b[0]<<endl;
                if(cut[j]==b[j] || b[j]=='?')  //判断字符串是否是子串
                {
                    flag=1;
                }
                else
                {
                    flag=0;
                    break;
                }    
            }
            if(flag==1)//如果是子串，检查是否有重复的
            {
                //cout<<cut<<endl;
                int flag2=0;
                for(auto k=s.begin();k!=s.end() && !s.empty();++k)
                {
                    if(*k==cut)
                    {
                        flag2=1;
                    }
                }
                if(flag2==0)  //没有重复的，将字符串添加进容器，数量+1
                {
                    s.push_back(cut);
                    //cout<<cut<<endl;
                    count++;
                }
            }
        }
        cout<<count<<endl;
        return;
    }
private:
    string a;
    string b;
    vector<string> s;
};

int main()
{
    solution aa;
    aa.fun();
    return 0;
}