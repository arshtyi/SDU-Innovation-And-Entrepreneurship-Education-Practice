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

void _() {
    string op;
    ll n, cnt = 0, top = -1;
    bool ht = 0;
    map<ll, ll> mp;
    vector<ll> q;
    cin >> n;
    FF(int, i, 1, n) {
        ll x;
        cnt++;
        cin >> op;
        if (op == "Add") {
            cin >> x;
            if (mp.count(x))
                printf("OpId #%lld: same likeness.\n", cnt);
            else {
                mp[x] = 0;
                q.eb(x);
                printf("OpId #%lld: success.\n", cnt);
            }
        } else if (op == "Close") {
            cin >> x;
            if (mp.count(x)) {
                printf("OpId #%lld: close %lld with %lld.\n", cnt, x, mp[x]);
                q.erase(find(all(q), x));
                mp.erase(x);
                if (top == x)
                    ht = false;
            } else
                printf("OpId #%lld: invalid likeness.\n", cnt);
        } else if (op == "Chat") {
            cin >> x;
            if (ht) {
                mp[top] += x;
                printf("OpId #%lld: success.\n", cnt);
            } else if (!q.empty()) {
                mp[q.front()] += x;
                printf("OpId #%lld: success.\n", cnt);
            } else
                printf("OpId #%lld: empty.\n", cnt);
        } else if (op == "Rotate") {
            cin >> x;
            if (x < 1 || x > q.size())
                printf("OpId #%lld: out of range.\n", cnt);
            else {
                q.insert(q.begin(), q[x - 1]);
                q.erase(q.begin() + x);
                printf("OpId #%lld: success.\n", cnt);
            }
        } else if (op == "Prior") {
            if (q.empty())
                printf("OpId #%lld: empty.\n", cnt);
            else {
                printf("OpId #%lld: success.\n", cnt);
                auto it = max_element(all(q));
                auto big = *it;
                q.erase(it);
                q.insert(q.begin(), big);
            }
        } else if (op == "Choose") {
            cin >> x;
            if (mp.count(x)) {
                printf("OpId #%lld: success.\n", cnt);
                auto it = find(all(q), x);
                auto u = *it;
                q.erase(it);
                q.insert(q.begin(), u);
            } else
                printf("OpId #%lld: invalid likeness.\n", cnt);
        } else if (op == "Top") {
            cin >> x;
            if (mp.count(x)) {
                printf("OpId #%lld: success.\n", cnt);
                top = x, ht = true;
            } else
                printf("OpId #%lld: invalid likeness.\n", cnt);
        } else if (op == "Untop") {
            if (ht) {
                printf("OpId #%lld: success.\n", cnt);
                ht = false;
            } else
                printf("OpId #%lld: no such person.\n", cnt);
        }
    }
    if (ht && mp[top]) {
        printf("OpId #%lld: Bye %lld: %lld.\n", ++cnt, top, mp[top]);
        q.erase(find(all(q), top));
        mp.erase(top);
    }
    for (auto& i : q)
        if (mp[i])
            printf("OpId #%lld: Bye %lld: %lld.\n", ++cnt, i, mp[i]);
}
signed main() {
    // local;
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while (T--)
        _();
    return 0;
}
