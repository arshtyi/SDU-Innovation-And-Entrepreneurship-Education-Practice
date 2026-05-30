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
    int n;
    string t;
    cin >> n >> t;
    string s = "01";
    while ((int)s.size() < n) {
        int len = s.size();
        F(int, i, 0, len) {
            if ((int)s.size() == n)
                break;
            s += (s[i] == '0' ? '1' : '0');
        }
    }
    int m = t.size();
    vector<int> nxt(m);
    F(int, i, 1, m) {
        int j = nxt[i - 1];
        while (j && t[i] != t[j])
            j = nxt[j - 1];
        if (t[i] == t[j])
            ++j;
        nxt[i] = j;
    }
    ll ans = 0;
    int j = 0;
    F(int, i, 0, n) {
        while (j && s[i] != t[j])
            j = nxt[j - 1];
        if (s[i] == t[j])
            ++j;
        if (j == m) {
            ++ans;
            j = nxt[j - 1];
        }
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
