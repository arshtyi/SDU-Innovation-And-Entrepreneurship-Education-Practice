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
void _() {
    int m;
    ll p;
    cin >> m >> p;
    int base = 1;
    while (base < m)
        base <<= 1;
    vector<ll> tr(base << 1, -1);
    auto add = [&](int pos, ll val) {
        int x = pos + base - 1;
        tr[x] = val;
        for (x >>= 1; x; x >>= 1)
            tr[x] = max(tr[x << 1], tr[x << 1 | 1]);
    };
    auto query = [&](int l, int r) {
        ll ans = -1;
        l += base - 1, r += base - 1;
        while (l <= r) {
            if (l & 1)
                ans = max(ans, tr[l++]);
            if (!(r & 1))
                ans = max(ans, tr[r--]);
            l >>= 1, r >>= 1;
        }
        return ans;
    };
    int cnt = 0;
    ll a = 0;
    FF(int, i, 1, m) {
        char op;
        ll x;
        cin >> op >> x;
        if (op == 'A') {
            add(++cnt, (x + a) % p);
        } else {
            a = query(cnt - (int)x + 1, cnt);
            cout << a << endl;
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
