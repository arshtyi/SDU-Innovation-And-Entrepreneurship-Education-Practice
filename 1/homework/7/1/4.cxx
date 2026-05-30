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
const int N = 100005;
int n, vis[N], d1[N], d2[N], tot, maxv;
vector<int> head(N, -1);
struct Edge {
    int to, w, next;
} edges[2 * N];

void add(int u, int v, int w) {
    edges[tot] = {v, w, head[u]};
    head[u] = tot++;
}

void dfs(int u, int depth, int* d) {
    d[u] = depth;
    vis[u] = 1;
    if (d[maxv] < d[u])
        maxv = u;
    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to, w = edges[e].w;
        if (vis[v] == 1)
            continue;
        dfs(v, depth + w, d);
    }
}
void _() {
    cin >> n;
    F(int, i, 1, n) {
        int u, v;
        cin >> u >> v;
        add(u, v, 1), add(v, u, 1);
    }
    memset(vis, 0, sizeof(vis));
    d1[maxv] = 0;
    dfs(1, 0, d1);
    memset(vis, 0, sizeof(vis));
    d1[maxv] = 0;
    dfs(maxv, 0, d1);
    memset(vis, 0, sizeof(vis));
    d2[maxv] = 0;
    dfs(maxv, 0, d2);
    FF(int, i, 1, n)
    cout << max(d1[i], d2[i]) << " ";
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
