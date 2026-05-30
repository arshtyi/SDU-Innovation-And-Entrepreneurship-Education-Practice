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
struct BIT {
    int n;
    vector<int> tree;
    BIT(int n = 0)
        : n(n)
        , tree(n + 1, 0) {}
    void add(int x, int val) {
        for (; x <= n; x += x & -x)
            tree[x] += val;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x)
            res += tree[x];
        return res;
    }
};

void _() {
    int n;
    cin >> n;
    vector<pii> a(n);
    vector<int> mem;
    F(int, i, 0, n) {
        cin >> a[i].fi >> a[i].se;
        mem.pb(a[i].se);
    }
    sort(all(mem));
    mem.erase(unique(all(mem)), mem.end());
    sort(all(a));
    BIT bit(mem.size());
    vector<int> ans(n, 0);
    for (auto [t, m] : a) {
        int id = lower_bound(all(mem), m) - mem.begin() + 1;
        int score = bit.query(id);
        ++ans[score];
        bit.add(id, 1);
    }
    F(int, i, 0, n) cout << ans[i] << endl;
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
