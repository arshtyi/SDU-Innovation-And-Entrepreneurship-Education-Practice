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
// const int M = 1e9 + 7;
// #define int ll
const int N = 1e5 + 10, M = 1e9 + 7;
ll n, m, cnt, r, c, b;
ll cf[25][100005];
ll prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % M;
        a = a * a % M, b >>= 1;
    }
    return res;
}
void f()
{
    for (ll i = 0, the_c = c; i < 25; ++i)
    {
        if (the_c == 1)
            break;
        while (the_c % prime[i] == 0)
        {
            the_c /= prime[i];
            cf[i][cnt] += b, cf[i][r + 1] -= b;
        }
    }
}
void GCD()
{
    ll res = 1;
    for (ll i = 0; i < 25; ++i)
    {
        ll sum = 0, mi = 1LL << (sizeof(ll) * 8 - 2);
        for (ll k = 1; k <= n; ++k)
            sum += cf[i][k], mi = min(mi, sum);
        res = (res % M) * (qpow(prime[i], mi) % M);
    }
    cout << res % M;
}
void _()
{
    cin >> n >> m;
    while (m--)
    {
        cin >> cnt >> r >> c >> b;
        f();
    }
    GCD();
}
signed main()
{
    int T = 1;
    // cin >> T;
    while (T--)
        _();
}
