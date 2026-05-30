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
struct Graph {
    vector<int> head, to, nxt, w;
    int idx = 0;
    Graph(int n, int m)
        : head(n + 1, -1)
        , to(m)
        , nxt(m)
        , w(m) {}
    void add(int u, int v, int c) {
        to[idx] = v;
        w[idx] = c;
        nxt[idx] = head[u];
        head[u] = idx++;
    }
};

vector<ll> dijkstra(const Graph& g, int n) {
    vector<ll> dis(n + 1, LLINF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dis[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dis[u])
            continue;
        for (int i = g.head[u]; i != -1; i = g.nxt[i]) {
            int v = g.to[i], c = g.w[i];
            if (dis[v] > d + c) {
                dis[v] = d + c;
                pq.push({dis[v], v});
            }
        }
    }
    return dis;
}

void _() {
    int n, m;
    cin >> n >> m;
    Graph g(n, m), rg(n, m);
    F(int, i, 0, m) {
        int s, e, c;
        cin >> s >> e >> c;
        g.add(s, e, c);
        rg.add(e, s, c);
    }

    vector<ll> go = dijkstra(g, n);
    vector<ll> back = dijkstra(rg, n);

    ll ans = 0;
    FF(int, i, 2, n) ans += go[i] + back[i];
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
