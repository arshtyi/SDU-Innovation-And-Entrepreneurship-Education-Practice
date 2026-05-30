#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define F(T, i, a, b) for (T i = (a); i < (b); ++i)
#define FF(T, i, a, b) for (T i = (a); i <= (b); ++i)
#define R(T, i, a, b) for (T i = (a); i > (b); --i)
#define RR(T, i, a, b) for (T i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define allab(x, a, b) (x).begin() + (a), (x).begin() + (b)
#define rallab(x, a, b) (x).rbegin() + (a), (x).rbegin() + (b)
#define pb push_back
#define eb emplace_back
#define pf push_front
#define ef emplace_front
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const int M1 = 1e9 + 7, M2 = 998244353;
#define endl '\n'
#define local freopen("data.in", "r", stdin)
#define locall freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
// #define int ll
const int N = 1e6 + 10;
ll tree[4 * N], lazy[4 * N], arr[N];
int lc(int x) {
    return x << 1;
}
int rc(int x) {
    return x << 1 | 1;
}
void pushup(int x) {
    tree[x] = tree[lc(x)] + tree[rc(x)];
}
void build(int x, int l, int r) {
    if (l == r) {
        tree[x] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(x), l, mid), build(rc(x), mid + 1, r), pushup(x);
}
void pushdown(int x, int l, int r) {
    if (lazy[x]) {
        int mid = (l + r) >> 1;
        tree[lc(x)] += lazy[x] * (mid - l + 1), tree[rc(x)] += lazy[x] * (r - mid);
        lazy[lc(x)] += lazy[x], lazy[rc(x)] += lazy[x], lazy[x] = 0;
    }
}
void update(int x, int l, int r, int ul, int ur, int val) {
    if (ul <= l && r <= ur) {
        tree[x] += val * (r - l + 1), lazy[x] += val;
        return;
    }
    pushdown(x, l, r);
    int mid = (l + r) >> 1;
    if (ul <= mid)
        update(lc(x), l, mid, ul, ur, val);
    if (ur > mid)
        update(rc(x), mid + 1, r, ul, ur, val);
    pushup(x);
}
ll query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x];
    pushdown(x, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid)
        res += query(lc(x), l, mid, ql, qr);
    if (qr > mid)
        res += query(rc(x), mid + 1, r, ql, qr);
    return res;
}
void _() {
    int n, q;
    cin >> n >> q;
    FF(int, i, 1, n) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, val;
            cin >> x >> val;
            update(1, 1, n, x, x, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << endl;
        }
    }
}
signed main() {
    // local;
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _();
    return 0;
}
