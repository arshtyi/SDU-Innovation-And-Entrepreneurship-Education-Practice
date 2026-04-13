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
const int INF = 0x3f3f3f3f3f3f3f3f;
const int M1 = 1e9 + 7, M2 = 998244353;
#define endl '\n'
#define local freopen("data.in", "r", stdin)
#define locall freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
// #define int ll
#define FILE 0
#define DIRE 1
ll LD, LR, file_sz;
struct node
{
    unordered_map<string, node *> dir;
    int type;
    ll ld, lr, sd, sr;
    node(int t) : ld(0), lr(0), sd(0), sr(0), type(t) {}
};
string op, pa;
vector<string> path;
node *root = new node(DIRE);
void prase()
{
    path.pb("/");
    stringstream ss(pa);
    string s;
    while (getline(ss, s, '/'))
        if (!s.empty())
            path.pb(s);
}
bool add(node *r, int u, int old_size)
{
    bool end = u + 1 == path.size();
    if (!end && r->lr && r->lr < r->sr + file_sz - old_size)
        return false;
    bool hc = false;
    if (r->dir[path[u]])
    {
        if (end && r->dir[path[u]]->type != FILE)
            return false;
        if (!end && r->dir[path[u]]->type != DIRE)
            return false;
    }
    else if (end)
    {
        r->dir[path[u]] = new node(FILE);
        hc = true;
    }
    else
    {
        r->dir[path[u]] = new node(DIRE);
        hc = true;
    }
    node *next = r->dir[path[u]];
    if (end)
    {
        ll modify = file_sz - next->sr;
        if ((r->ld && r->ld < r->sd + modify) || (r->lr && r->lr < r->sr + modify))
        {
            if (hc)
                r->dir[path[u]] = nullptr;
            return false;
        }
        next->sr = file_sz;
        r->sd += modify, r->sr += modify;
        return true;
    }
    if (add(next, u + 1, old_size))
    {
        r->sr += file_sz - old_size;
        return true;
    }
    if (hc)
        r->dir[path[u]] = nullptr;
    return false;
}
ll del(node *r, int u)
{
    if (r->dir[path[u]] == nullptr)
        return 0;
    bool end = u + 1 == path.size();
    if (!end && r->dir[path[u]]->type != DIRE)
        return 0;
    if (end)
    {
        ll res = r->dir[path[u]]->sr;
        if (r->dir[path[u]]->type == FILE)
            r->sd -= res;
        r->dir[path[u]] = nullptr;
        r->sr -= res;
        return res;
    }
    ll res = del(r->dir[path[u]], u + 1);
    r->sr -= res;
    return res;
}
bool reset(node *r, int u)
{
    if (r->dir[path[u]] == nullptr)
        return false;
    bool end = u + 1 == path.size();
    if (!end && r->dir[path[u]]->type != DIRE)
        return false;
    node *next = r->dir[path[u]];
    if (end)
    {
        if (next->type != DIRE)
            return false;
        if ((LD && LD < next->sd) || (LR && LR < next->sr))
            return false;
        next->ld = LD, next->lr = LR;
        return true;
    }
    return reset(next, u + 1);
}
ll get_size(node *r, int u)
{
    bool end = u + 1 == path.size();
    if (r->dir[path[u]] == nullptr)
        return 0;
    if (!end && r->dir[path[u]]->type != DIRE)
        return 0;
    if (end && r->dir[path[u]]->type != FILE)
        return 0;
    if (end)
        return r->dir[path[u]]->sr;
    return get_size(r->dir[path[u]], u + 1);
}
void _()
{
    root->dir["/"] = new node(DIRE);
    int n;
    cin >> n;
    FF(int, i, 1, n)
    {
        cin >> op >> pa;
        path.clear();
        prase();
        if (op == "C")
        {
            cin >> file_sz;
            if (add(root, 0, get_size(root, 0)))
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
        else if (op == "R")
        {
            del(root, 0);
            cout << "Y" << endl;
        }
        else
        {
            cin >> LD >> LR;
            if (reset(root, 0))
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
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
