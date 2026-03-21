#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
typedef unsigned __int128 LLL;
typedef float fl;
typedef double db;
typedef long double ld;
// #define fio
#ifdef fio
char buf[1 << 20], *p1, *p2, pbuf[1 << 20], *pp = pbuf;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#define pc(c) (pp - pbuf == (1 << 20) ? (fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf, *pp++ = (c)) : (*pp++ = (c)))
#else
#define gc getchar
// #define gc getchar_unlocked
#define pc putchar
#endif
#define F(i, a, b) for (int i = (a); i < (b); ++i)
#define FF(i, a, b) for (int i = (a); i <= (b); ++i)
#define R(i, a, b) for (int i = (a); i > (b); --i)
#define RR(i, a, b) for (int i = (a); i >= (b); --i)
#define unsync cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define endl '\n'
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define eb emplace_back
#define mkp make_pair
#define mkt make_tuple
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pdd pair<double, double>
#define fi first
#define se second
#define cs const
#define vec vector
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define local freopen("data.in", "r", stdin)
#define locall freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
// #define int long long
template <typename T>
void read(T &t)
{
    t = 0;
    bool f = 1;
    char x = gc();
    while (x < '0' || x > '9')
    {
        if (x == '-')
            f = 0;
        x = gc();
    }
    while (x >= '0' && x <= '9')
        t = (t << 1) + (t << 3) + (x ^ '0'), x = gc();
    t = f ? t : -t;
    return;
}
template <typename T>
void write(T t)
{
    bool f = false;
    if (t < 0)
        f = true, pc('-'), t = -t;
    static int sta[40];
    int top = 0;
    do
    {
        sta[top++] = t % 10, t /= 10;
    } while (t);
    while (top)
        pc('0' + sta[--top]);
    return;
}
bool iso(int n, int k) { return n % k == 0 || n % 10 == k; }
void sol()
{
    int n, k;
    cin >> n >> k;
    // cout << n << " " << k << endl;
    vec<int> child;
    FF(i, 1, n)
    child.pb(i);
    int idx = 0, cnt = 1;
    while (child.size() > 1)
    {
        if (iso(cnt, k))
        {
            child.erase(child.begin() + idx);
            if (idx == child.size())
                idx = 0;
        }
        else
            idx = (idx + 1) % child.size();
        cnt++;
    }
    cout << child[0] << endl;
}
signed main()
{
    // local;
    unsync;
    int T = 1; // cin >> T;
    while (T--)
        sol();
    return 0;
}
