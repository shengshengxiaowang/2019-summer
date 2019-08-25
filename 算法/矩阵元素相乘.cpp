/*A[n,m]是一个n行m列的矩阵，a[i,j]表示A的第i行j列的元素，
定义x[i,j]为A的第i行和第j列除了a[i,j]之外所有元素(共n+m-2个)的乘积，
即x[i,j]=a[i,1]*a[i,2]*...*a[i,j-1]*...*a[i,m]*a[1,j]*a[2,j]...*a[i-1,j]*a[i+1,j]...*a[n,j],
现输入非负整形的矩阵A[n,m]，求MAX(x[i,j])，即所有的x[i,j]中的最大值。

思路：我的思路是开始先将每行每列的乘积都算出来，放入x、y数组中，然后依次遍历矩阵中的每个值，
将所在位置的行、列的乘积在x、y中找到，除两遍本身的值就行了
但是我忽略了有0的情况，如果一行或一列中只有一个0.那么在刚开始x、y数组中这整个乘积都为0
那么当算到这个0的时候，这行或这列的值应该是不为0的
我在评论区里看到的思路，解决了这个问题，将为0的数，变成-1，在计算最大值的时候不影响，在计算乘积的时候也不影响
*/
#include<iostream>
using namespace std;

class a
{
public:
    void fun()
    {
        int m,n;
        while(cin>>n>>m)
        {
            int a[n][m];
            int x[n],y[m];
            int i,j;
            for(i=0;i<n;i++)
            {
                int s=1;
                for(j=0;j<m;j++)
                {
                    cin>>a[i][j];
                    if(a[i][j]==0)
                    {
                        a[i][j]=-1;
                    }
                    s=s*a[i][j];
                }
                x[i]=s;
                //cout<<s<<endl;
            }
            for(i=0;i<m;i++)
            {
                int s=1;
                for(j=0;j<n;j++)
                {
                    s=s*a[j][i];
                }
                y[i]=s;
                //cout<<s<<endl;
            }
            
            int maxx=0;
            for(i=0;i<n;i++)
            {
                for(j=0;j<m;j++)
                {
                    int k=0;
                    k=x[i]*y[j]/a[i][j]/a[i][j];
                   
                    maxx=max(maxx,k);
                }
            }

            cout<<maxx<<endl;
        }
    }
};

int main()
{
    a bb;
    bb.fun();

}