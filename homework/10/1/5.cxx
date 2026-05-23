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
    int to, c, d;
};

bool check(int n, int limit_time, int need, const vector<vector<Edge>>& g) {
    vector<ll> dis(n + 1, LLINF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dis[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();
        if (dist != dis[u])
            continue;
        if (u == n)
            return dist <= limit_time;
        if (dist > limit_time)
            continue;

        for (auto [v, c, d] : g[u]) {
            if (c < need)
                continue;
            ll nd = dist + d;
            if (nd < dis[v] && nd <= limit_time) {
                dis[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dis[n] <= limit_time;
}

void _() {
    int n, m, t;
    cin >> n >> m >> t;
    vector<vector<Edge>> g(n + 1);
    int max_c = 0;
    F(int, i, 0, m) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        g[a].pb({b, c, d});
        g[b].pb({a, c, d});
        max_c = max(max_c, c);
    }
    int l = 1, r = max_c, ans = 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(n, t, mid, g)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
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
