#include<bits/stdc++.h>
using namespace std;
#define lb(x) (x)&(-(x))
//树状数组改良时间复杂度
const int maxn=1e6;
int n;
int num[maxn+30];
int f[maxn+30];
bool flag[maxn+30];
int ans;
int bit[maxn + 30];
vector<pair<int, int>> pairs;

int sum(int i) {
    int res = 0;
    while (i > 0) {
        res = max(res, bit[i]);
        i -= lb(i);
    }
    return res;
}

void update(int i, int val) {
    while (i <= n) {
        bit[i] = max(bit[i], val);
        i += lb(i);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    f[1]=1;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
        pairs.push_back({num[i], i}); // 存储数值及其对应的位置
    }
    sort(pairs.begin(), pairs.end()); // 按数值大小排序
    int rank=1;
    for (int i = 0; i < n; i++) {
        if (i > 0 && pairs[i].first != pairs[i - 1].first) rank++;
        num[pairs[i].second] = rank; // 将位置重新映射为排名
    }
    memset(flag, 0 ,sizeof flag);
    for (int i = 1; i <= n; i++) {
        if(!flag[num[i]]) f[i] = sum(num[i])+1,flag[num[i]]=1,update(num[i], f[i]);
        else f[i]=sum(num[i])+1;
        ans = max(ans, f[i]);
    }
    for(int i=1;i<=n;i++) cout<<num[i]<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++) cout<<f[i]<<" ";
    cout << ans << "\n";
    return 0;
}