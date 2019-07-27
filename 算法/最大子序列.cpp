/*
对于字符串x和y, 如果擦除x中的某些字母(有可能全擦掉或者都不擦)能够得到y,我们就称y是x的子序列。例如."ncd"是"nowcoder"的子序列,而"xt"不是。
现在对于给定的一个字符串s,请计算出字典序最大的s的子序列。

写的纯c风格的emmmmmm
字典序意思就是先比较第一个，第一个大就OK，，一样再比较第二个
所以倒着遍历字符串即可
*/




#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
char ss[50];
class solution
{
public:
    //vector<char> fun(vector<char> s)
    void fun()
    {
        char s[50];
        cin>>s;
        int j=0;
        int k=strlen(s)-1;
        ss[0]=s[k];
        for(int i=k-1;i>=0;i--)
        {
            if(s[i]>=ss[j])
            {
                ss[++j]=s[i];
            }
        }
        
        
    } 
};

int main()
{
    solution aa;
    aa.fun();
    for(int i=strlen(ss)-1;i>=0;i--)
    {
        cout<<ss[i];
    }
    cout<<endl;
}