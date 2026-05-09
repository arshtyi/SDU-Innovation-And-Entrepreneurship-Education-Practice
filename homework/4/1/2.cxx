#include <bits/stdc++.h>
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
int n;
void _() {
    string s;
    cin >> n >> s;
    vector<int> cnt(26, 0);
    int unique = 0, ans = n + 1;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        int idx = s[r] - 'A';
        if (++cnt[idx] == 1)
            unique++;
        while (unique == 26) {
            ans = min(ans, r - l + 1);
            int lidx = s[l] - 'A';
            if (--cnt[lidx] == 0)
                unique--;
            l++;
        }
    }
    if (ans == n + 1)
        cout << -1 << endl;
    else
        cout << ans << endl;
}
signed main() {
    int T = 1;
    // cin >> T;
    while (T--)
        _();
}
