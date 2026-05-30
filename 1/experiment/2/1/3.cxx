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
const int N = 505;
int G[N][N], n, m, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0}, cnt;
void _() {
    cin >> n >> m;
    FF(int, i, 1, n)
    FF(int, j, 1, m)
    cin >> G[i][j];
    FF(int, i, 1, n)
    FF(int, j, 1, m) {
        int f = 1;
        F(int, k, 0, 4) {
            int x = i + dx[k], y = j + dy[k];
            if (x > 0 && x <= n && y > 0 && y <= m)
                f &= (G[i][j] > G[x][y]);
        }
        // if (f)
        //     cout << i << " " << j << " " << G[i][j] << endl;
        cnt += f;
    }
    cout << cnt << endl;
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
