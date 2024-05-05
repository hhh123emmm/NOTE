#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using pii = pair<int, int>;
const int N = 5e5 + 55, inf = 0x3f3f3f3f, MOD = 1e9 + 7;
int n, m, DFN;
i64 dat[N];
int dep[N], Size[N], son[N], id[N];
int fa[N], top[N], c[N];
vector<vector<int> > G;

void dfs(int x, int depth) {
    dep[x] = depth, Size[x] = 1;
    int maxs = 0, t = 0;
    for (auto v : G[x]) {
        fa[v] = x;
        dfs(v, depth + 1);
        Size[x] += Size[v];
        if (Size[v] > maxs) {
            maxs = Size[v];
            t = v;
        }
    }
    if (t) son[x] = t;
}

void dfs2(int x, int topp) {
    id[x] = ++DFN, top[x] = topp;
    if (son[x]) {
        dfs2(son[x], topp);
    } else {
        return;
    }
    for (auto v : G[x]) {
        if (v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}

inline int lowbit(int x) { return x & -x; }

void update(int x, int k) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c[i] += k;
    }
}

int query(int l, int r) {
    int ret = 0;
    for (int i = r; i; i -= lowbit(i)) {
        ret += c[i];
    }
    for (int i = l - 1; i; i -= lowbit(i)) {
        ret -= c[i];
    }
    return ret;
}

int Query(int x, int y) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            ret += query(id[top[y]], id[y]);
            y = fa[top[y]];
        } else {
            ret += query(id[top[x]], id[x]);
            x = fa[top[x]];
        }

    }
    if (dep[x] > dep[y]) {
        ret += query(id[y], id[x]);
    } else {
        ret += query(id[x], id[y]);
    }
    return ret;
}

pair<size_t, i64> merge(int x) {
    vector<int> sonx = std::move(G[x]);
    // G[x].swap(std::vector<int>());
    G[x].clear();
    for (auto v : sonx) {
        if (G[v].size() > G[x].size()) std::swap(G[x], G[v]);
        for (auto t : G[v]) {
            G[x].push_back(t);
        }
        dat[x] += dat[v];
        // G[v].swap(std::vector<int>());
        G[v].clear();
        update(id[v], -1);
    }
    return make_pair(G[x].size(), dat[x]);
}

signed main() {
#ifdef LRL52
    freopen("E.in", "r", stdin);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    G.resize(n + 1);
    for (int i = 2; i <= n; ++i) {
        int par;
        cin >> par;
        G[par].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> dat[i];
    }
    dfs(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            auto ans = merge(x);
            cout << ans.first << " " << ans.second << "\n";
        } else {
            int dx = Query(1, x);
            cout << dep[x] + 1 + dx << "\n";
        }
    }
    return 0;
}