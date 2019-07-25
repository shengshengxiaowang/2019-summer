/*
小度有一个小写字母组成的字符串s.字符串s已经被写在墙上了.
小度还有很多卡片,每个卡片上有一个小写字母,组成一个字符串t。
小度可以选择字符串t中任意一个字符,然后覆盖在字符串s的一个字符之上。小度想知道在选取一些卡片覆盖s的一些字符之后,
可以得到的字典序最大的字符串是什么。

将卡片的字符串降序排序，然后正序遍历墙上字符串，卡片比墙上大就粘
*/

#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;


class solution
{
public:
    static bool cmp(char a, char b)//static 问题
    {
        return a>b;
    }
    void fun()
    {
        cin>>s;
        cin>>ss;
        int l=strlen(s);
        int ll=strlen(ss);
        sort(ss,ss+ll,cmp);
        int k=0;
        for(int i=0;i<l;i++)
        {
            if(ss[k]>s[i] && k!=ll)
            {
                s[i]=ss[k++];
            }
            cout<<s[i];
        }
        cout<<endl;
    }
private:
    char s[51];  //这里如果是50的话就有问题，不知道为啥，待解决
    char ss[51];
};

int main()
{
    solution aa;
    aa.fun();
    
}