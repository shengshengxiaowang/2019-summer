/*
在商城的某个位置有一个商品列表，该列表是由L1、L2两个子列表拼接而成。当用户浏览并翻页时，需要从列表L1、L2中获取商品进行展示。展示规则如下：
1. 用户可以进行多次翻页，用offset表示用户在之前页面已经浏览的商品数量，比如offset为4，表示用户已经看了4个商品
2. n表示当前页面需要展示的商品数量
3. 展示商品时首先使用列表L1，如果列表L1长度不够，再从列表L2中选取商品
4. 从列表L2中补全商品时，也可能存在数量不足的情况
请根据上述规则，计算列表L1和L2中哪些商品在当前页面被展示了
输入描述:
每个测试输入包含1个测试用例，包含四个整数，分别表示偏移量offset、元素数量n，列表L1的长度l1，列表L2的长度l2。
输出描述:
在一行内输出四个整数分别表示L1和L2的区间start1，end1，start2，end2，每个数字之间有一个空格。
注意，区间段使用半开半闭区间表示，即包含起点，不包含终点。如果某个列表的区间为空，使用[0, 0)表示，如果某个列表被跳过，使用[len, len)表示，len表示列表的长度。
*/


#include<iostream>
using namespace std;

class solution
{
public:
    void fun()
    {
        int formal,n,l1,l2;
        while(cin>>formal>>n>>l1>>l2)
        {
            int str1=l1,str2=l2,end1=l1,end2=l2;
            if(formal<l1)  //如果开始区间在列表1中
            {
                str1=formal;            //开始就是开始
                end1=min(l1,formal+n);  //第一个结束就是列表尾跟总的哪个小是哪个
                str2=0;                 //第二个开始则就算到也是0，没到也是0
                end2=max(0,formal+n-l1);  //第二个结束则是0跟总数减去列表1数哪个大是哪个

            }
            if(formal>=l1 && formal<l1+l2)    //如果开始区间在列表2中
            {
                str2=formal-l1;
                end2=min(l2,n+formal-l1);
            }
            cout<<str1<<' '<<end1<<' '<<str2<<' '<<end2<<endl;
        }
    }
};

int main()
{
    solution aa;
    aa.fun();
}


/*
//大佬的代码：
#include <algorithm>
#include <cstdio>
using namespace std;
int main() {
    int offset, n, l1, l2;
    while (~scanf("%d%d%d%d", &offset, &n, &l1, &l2))
        printf("%d %d %d %d\n", min(l1, offset), min(l1, offset+n), min(
               max(offset-l1, 0), l2), min(max(offset+n-l1, 0), l2));
    return 0;
}

*/