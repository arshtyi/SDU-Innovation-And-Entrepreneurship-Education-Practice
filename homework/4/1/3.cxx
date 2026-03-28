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
const int N = 1e6 + 10, NN = 20;
int st1[N][NN], arr[N], st2[N][NN];
void build(int n)
{
    FF(i, 1, n)
    st1[i][0] = arr[i], st2[i][0] = arr[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st1[i][j] = max(st1[i][j - 1], st1[i + (1 << (j - 1))][j - 1]), st2[i][j] = min(st2[i][j - 1], st2[i + (1 << (j - 1))][j - 1]);
}
pii query(int l, int r)
{
    int lt = r - l + 1, q = floor(log2(lt));
    return {max(st1[l][q], st1[r - (1 << q) + 1][q]), min(st2[l][q], st2[r - (1 << q) + 1][q])};
}
int n, k;
vector<int> mires, mares;
void _()
{
    cin >> n >> k;
    FF(i, 1, n)
    cin >> arr[i];
    build(n);
    for (int i = 1; i + k - 1 <= n; ++i)
    {
        auto [mx, mn] = query(i, i + k - 1);
        mires.pb(mn), mares.pb(mx);
    }
    for (auto x : mires)
        cout << x << " ";
    cout << endl;
    for (auto x : mares)
        cout << x << " ";
    cout << endl;
}
signed main()
{
    int T = 1;
    // cin >> T;
    while (T--)
        _();
}
