//最长公共子序列------------------震惊，时间复杂度一点没卡
#include<bits/stdc++.h>
using namespace std;

const int maxn=5e3;
int a[maxn+30],b[maxn+30];
int n,m;
int f[maxn+30][maxn+30];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    f[1][0]=f[0][1]=f[0][0]=0;
    // int i=1,j=1;
    // while(i<=n&&j<=m){
    //     if(a[i]==b[j]){
    //         f[i][j]=f[i-1][j-1]+1;
    //     }else{
    //         f[i][j]=max(f[i-1][j],f[i][j-1]);
    //     }
    //     i++,j++;
    // }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i]==b[j]){
                f[i][j]=f[i-1][j-1]+1;
            }else{
                f[i][j]=max(f[i-1][j],f[i][j-1]);
            }
        }
    }
    printf("%d",f[n][m]);
}