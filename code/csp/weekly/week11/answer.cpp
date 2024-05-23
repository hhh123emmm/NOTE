#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
int n, dat[2 * MAXN - 1];

void init(int n_) {
    n = 1;
    while (n < n_) n *= 2;
    for (int i = 0; i < 2 * n - 1; ++i) dat[i] = INT_MIN;
}

void update(int k, int a) {
    k += n - 1, dat[k] = a;
    while (k > 0) k = (k - 1) / 2, dat[k] = max(dat[k * 2 + 1], dat[k * 2 + 2]);
}

int query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INT_MIN;
    if (a <= l && r <= b) return dat[k];
    int vl = query(a, b, k * 2 + 1, l, (l + r) / 2), vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return max(vl, vr);
}

int main() {
    int m, p, a = 0, t, cnt = 0;
    char c;
    cin >> m >> p;
    init(200005);
    for (int i = 1; i <= m; ++i) {
        scanf(" %c %d", &c, &t);
        if (c == 'Q')
            a = query(cnt - t, cnt, 0, 0, n), printf("%d\n", a);
        else
            update(cnt++, (t + a) % p);
    }
}
