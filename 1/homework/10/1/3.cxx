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
struct Edge {
    int to, w;
};

bool has_negative_cycle(int n, vector<vector<Edge>>& g) {
    vector<int> dis(n + 1), cnt(n + 1), inq(n + 1, 1);
    queue<int> q;
    FF(int, i, 1, n) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (++cnt[v] >= n)
                    return true;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return false;
}

void _() {
    int n, m, w;
    cin >> n >> m >> w;
    vector<vector<Edge>> g(n + 1);
    F(int, i, 0, m) {
        int s, e, t;
        cin >> s >> e >> t;
        g[s].pb({e, t});
        g[e].pb({s, t});
    }
    F(int, i, 0, w) {
        int s, e, t;
        cin >> s >> e >> t;
        g[s].pb({e, -t});
    }
    cout << (has_negative_cycle(n, g) ? "YES" : "NO") << endl;
}
signed main() {
    // local;
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while (T--)
        _();
    return 0;
}
