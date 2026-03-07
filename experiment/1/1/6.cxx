#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll qpow(ll a, ll b)
{
    ll res = 1;
    do
    {
        if (b & 1)
            res *= a;
        a *= a;
    } while (b >>= 1);
    return res;
}
signed main()
{
    ll l, r, k;
    cin >> l >> r >> k;
    ll lk = log(l) / log(k), rk = log(r) / log(k);
    bool f = 0;
    for (ll i = lk; i <= rk; ++i)
    {
        ll x = qpow(k, i);
        if (x >= l && x <= r)
            f = 1, cout << x << " ";
    }
    if (!f)
        cout << -1 << endl;
}
