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
vector<int> a;
int n, k, t;
double eps = 1e-6, mid, ma, mi = 0;
bool check(double& len) {
    int cnt = 0;
    for (auto& i : a) {
        cnt += i / len;
        if (cnt >= k)
            return true;
    }
    return false;
}
void _() {
    cin >> n >> k;
    F(int, i, 0, n) {
        cin >> t;
        a.eb(t);
    }
    sort(all(a), greater<int>());
    ma = a[0];
    while (ma - mi > eps) {
        mid = (ma + mi) / 2;
        if (check(mid))
            mi = mid;
        else
            ma = mid;
    }
    cout << fixed << setprecision(6) << ma << endl;
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
