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
const int N = 1e5 + 10;
int n, m, ans;
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool unite(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return 0;
    fa[fx] = fy;
    return 1;
}
void _()
{
    cin >> n >> m;
    FF(int, i, 1, n)
    fa[i] = i;
    FF(int, i, 1, m)
    {
        int x, y;
        cin >> x >> y;
        if (unite(x, y))
            ans++;
        cout << n - ans - 1 << endl;
    }
}
signed main()
{
    // local;
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _();
    return 0;
}
