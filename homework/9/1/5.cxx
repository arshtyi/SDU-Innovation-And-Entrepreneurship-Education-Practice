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
const ll N = 50, V = 1e15 + 5;
using pll = pair<ll, ll>;
ll n, v, wi[N], vi[N];
void _() {
    cin >> n >> v;
    FF(int, i, 1, n) cin >> wi[i] >> vi[i];
    vector<pll> a, b;
    ll m = n >> 1;
    F(ll, s, 0, (1LL << m)) {
        ll sw = 0, sv = 0;
        F(ll, i, 0, m) if (s >> i & 1) sw += wi[i + 1], sv += vi[i + 1];
        if (sw <= v)
            a.eb(sw, sv);
    }
    F(ll, s, 0, (1LL << (n - m))) {
        ll sw = 0, sv = 0;
        F(ll, i, 0, n - m) if (s >> i & 1) sw += wi[m + i + 1], sv += vi[m + i + 1];
        if (sw <= v)
            b.eb(sw, sv);
    }
    sort(all(b));
    ll t = 0;
    for (auto [sw, sv] : b)
        if (!t || sv > b[t - 1].se)
            b[t++] = {sw, sv};
    b.resize(t);
    ll ans = 0;
    for (auto [sw, sv] : a) {
        ll p = upper_bound(all(b), make_pair(v - sw, LLINF)) - b.begin() - 1;
        if (p >= 0)
            ans = max(ans, sv + b[p].se);
    }
    cout << ans << endl;
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
