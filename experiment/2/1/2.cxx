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
string s;
string prog;
size_t prog_pos = 0;
static bool next_token(string &tok)
{
    tok.clear();
    while (prog_pos < prog.size() && isspace((unsigned char)prog[prog_pos]))
        ++prog_pos;
    if (prog_pos >= prog.size())
        return false;
    if (prog.compare(prog_pos, 5, "BEGIN") == 0)
    {
        tok = "BEGIN";
        prog_pos += 5;
        return true;
    }
    if (prog.compare(prog_pos, 3, "END") == 0)
    {
        tok = "END";
        prog_pos += 3;
        return true;
    }
    if (prog.compare(prog_pos, 4, "LOOP") == 0)
    {
        tok = "LOOP";
        prog_pos += 4;
        return true;
    }
    if (prog.compare(prog_pos, 2, "OP") == 0)
    {
        tok = "OP";
        prog_pos += 2;
        return true;
    }
    if (prog[prog_pos] == 'n')
    {
        tok = "n";
        ++prog_pos;
        return true;
    }
    if (isdigit((unsigned char)prog[prog_pos]))
    {
        size_t st = prog_pos;
        while (prog_pos < prog.size() && isdigit((unsigned char)prog[prog_pos]))
            ++prog_pos;
        tok = prog.substr(st, prog_pos - st);
        return true;
    }
    ++prog_pos;
    return next_token(tok);
}

int solve(int *pol)
{
    if (!next_token(s))
        return 0;
    if (s[0] == 'E')
        return 0;
    if (s[0] == 'B')
        while (solve(pol))
            ;
    else if (s[0] == 'L')
    {
        int t = 0, t_pol[15] = {0};
        bool is_n = false;
        next_token(s);
        if (s[0] == 'n')
            is_n = true;
        else
        {
            stringstream stream;
            stream << s;
            stream >> t;
        }
        while (solve(t_pol))
            ;
        if (is_n)
        {
            RR(int, i, 10, 1)
            t_pol[i] = t_pol[i - 1];
            t_pol[0] = 0;
        }
        else
            FF(int, i, 0, 10)
        t_pol[i] *= t;
        FF(int, i, 0, 10)
        pol[i] += t_pol[i];
    }
    else
    {
        next_token(s);
        stringstream stream;
        stream << s;
        int tmp;
        stream >> tmp;
        pol[0] += tmp;
        return solve(pol);
    }
    return 1;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t = 0, pol[15] = {0};
    prog.assign((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    prog_pos = 0;
    solve(pol);
    cout << "Runtime = ";
    RR(int, j, 10, 0)
    {
        if (pol[j])
        {
            ++t;
            if (t != 1)
                cout << "+";
            if (pol[j] != 1 || j == 0)
                cout << pol[j];
            if ((pol[j] != 1) && (j > 0))
                cout << "*";
            if (j > 1)
                cout << "n^" << j;
            if (j == 1)
                cout << "n";
        }
    }
    if (!t)
        cout << "0";
    return 0;
}
