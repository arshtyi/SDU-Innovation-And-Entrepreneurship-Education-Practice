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
stack<pair<int, ll>> s;
long long a[1000100], L[1000010], R[1000010];
void find(ll Ans[])
{
    while (!s.empty())
        s.pop();
    FF(i, 1, n)
    {
        while (!s.empty() && s.top().second >= a[i])
            s.pop();
        if (s.empty())
            Ans[i] = i;
        else
            Ans[i] = i - s.top().first;
        s.push(pair<int, ll>(i, a[i]));
    }
}

int main()
{
    cin >> n;
    FF(i, 1, n)
    cin >> a[i];
    ll ans = 0;
    find(L);
    reverse(a + 1, a + n + 1);
    find(R);
    reverse(a + 1, a + n + 1);
    reverse(R + 1, R + n + 1);
    FF(i, 1, n)
    ans = max(ans, a[i] * (L[i] + R[i] - 1));
    cout << ans << endl;
    return 0;
}
