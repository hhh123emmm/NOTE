#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using pii = pair<int, int>;
const int N = 1e3 + 55, inf = 0x3f3f3f3f, MOD = 1e9 + 7;
const double Eps = 1e-8;

signed main() {
#ifdef LRL52
    freopen("C.in", "r", stdin);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int Task; cin >> Task;
    while (Task--) {
        int m;
        cin >> m;
        vector<unordered_map<string, int> > H(m + 1);
        unordered_set<string> S;
        for (int i = 1; i <= m; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < (int)s.size(); ) {
                int k1 = j - 1;
                while (k1 + 1 < (int)s.size() && !isdigit(s[k1 + 1])) ++k1;
                int k2 = k1;
                while (k2 + 1 < (int)s.size() && isdigit(s[k2 + 1])) ++k2;
                auto key = s.substr(j, k1 - j + 1);
                auto val = s.substr(k1 + 1, k2 - (k1 + 1) + 1);
                H[i][key] = H[i][key] + stoi(val);
                S.insert(key);
                j = k2 + 1;
            }
        }
        int n = S.size();
        vector<vector<double> > a(n + 1, vector<double>(m + 1));
        auto it = S.begin();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                a[i][j] = H[j][*it];
            }
            it = std::next(it);
        }
        int rank = 0;
        for (int i = 1; i <= n; ++i) {
            int r = i;
            for (int j = i + 1; j <= n; ++j) {
                if (fabs(a[j][i]) > fabs(a[r][i])) {
                    r = j;
                }
            }
            if (fabs(a[r][i]) < Eps) {
                continue;
            } else {
                ++rank;
            }
            if (r != i) {
                std::swap(a[i], a[r]);
            }
            for (int j = i + 1; j <= n; ++j) {
                const double div = a[j][i] / a[i][i];
                for (int k = i; k <= m; ++k) {
                    a[j][k] -= div * a[i][k];
                }
            }
        }
        if (rank < m) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}