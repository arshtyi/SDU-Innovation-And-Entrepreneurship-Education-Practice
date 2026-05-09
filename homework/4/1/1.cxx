#include <bits/stdc++.h>
#include <memory>
#include <queue>
using namespace std;
#define fi first
#define se second
#define F(i, a, b) for (int i = (a); i < (b); ++i)
#define FF(i, a, b) for (int i = (a); i <= (b); ++i)
#define R(i, a, b) for (int i = (a); i > (b); --i)
#define RR(i, a, b) for (int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
using ll = long long;
using pii = pair<int, int>;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const int M = 1e9 + 7;
// #define int ll
const int N = 5e5 + 5, NN = 26;
int cnt[N][NN];
int n, m;
void _() {
    cin >> n;
    FF(i, 1, n) {
        char c;
        cin >> c;
        F(j, 0, NN)
        cnt[i][j] = cnt[i - 1][j] + (c - 'A' == j);
    }
    // FF(i, 1, n)
    // F(j, 0, NN)
    // cout << cnt[i][j] << " \n"[j == NN - 1];
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--;
        int f = 1;
        F(i, 0, NN)
        f &= (cnt[r][i] - cnt[l][i] >= 1);
        cout << (f ? "YES\n" : "NO\n");
    }
}
signed main() {
    int T = 1;
    // cin >> T;
    while (T--)
        _();
}
