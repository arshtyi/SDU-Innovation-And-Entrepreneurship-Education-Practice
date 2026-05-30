#include <bits/stdc++.h>
#include <unordered_map>
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
const int N = 1e3 + 10, M = 102;
int n, V, dp[N];
vector<vector<pii>> G(M, vector<pii>());
void _() {
    cin >> n >> V;
    unordered_map<int, int> mp;
    FF(int, i, 1, n) {
        int wi, vi, ki;
        cin >> wi >> vi >> ki;
        if (!mp.count(ki))
            mp[ki]++;
        G[ki].eb(wi, vi);
    }
    int cnt = mp.size();
    F(int, i, 1, M)
    RR(int, j, V, 0) for (auto [wi, vi] : G[i]) if (j >= wi) dp[j] = max(dp[j], dp[j - wi] + vi);
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
