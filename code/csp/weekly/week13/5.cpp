#include <iostream>
#include<cstring> 
using namespace std;
const int maxn=1e5;
long long int  w[40+30],v[40+30],dp[maxn];
int main()
{
    int t;
    t=1;
    while(t--)
    {
        long long int i,j,n,c,V=0;
        cin>>n>>c;
        for(i=1;i<=n;i++) 
        {
            cin>>w[i];
            cin>>v[i];
            V+=v[i];
        }
        memset(dp,1000000010,sizeof(dp)); ///要求最小容量，初始化为最大值；
        dp[0]=0;
        for(i=1;i<=n;i++)
            for(int j = V ;j >= v[i];j--)
                dp[j]= min( dp[j] , dp[j-v[i]] + w [i]);
        for( i=V ;i>=0 ; i--)
            if(dp[i]<=c)
            {
               cout<<i<<endl; ///此处输出i，即为满足条件的最大价值
               break;
            }
        }
    return 0;    
}