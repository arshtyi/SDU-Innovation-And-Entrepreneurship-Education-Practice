#include <bits/stdc++.h>
#include <deque>
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
using pil = pair<int, ll>;
const int N = 1e4 + 10;
int n, V;
ll dp[N];
void _() {
    cin >> n >> V;
    FF(int, i, 1, n) {
        int mi, wi, vi;
        cin >> wi >> vi >> mi;
        int dj = mi * wi;
        F(int, j, 0, wi) {
            deque<pil> dq;
            dq.eb(j, dp[j]);
            for (int k = j + wi; k <= V; k += wi) {
                if (!dq.empty() && k - dq.front().fi > dj)
                    dq.pop_front();
                while (!dq.empty() && dq.back().se + (k - dq.back().fi) / wi * vi <= dp[k])
                    dq.pop_back();
                dq.eb(k, dp[k]);
                dp[k] = max(dp[k], dq.front().se + (k - dq.front().fi) / wi * vi);
            }
        }
    }
    cout << dp[V] << endl;
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
