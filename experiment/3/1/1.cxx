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
enum comd { home, en, le, ri, up, down, del, backspace };
string txt, copyTxt;
int remember = -1, now = -1;
bool selected = false, shifted = false, haveCopy = false;
int move(comd com) {
    selected = false;
    if (com == le) {
        if (now == -1)
            return 0;
        now--;
        return 1;
    } else if (com == ri) {
        if (now == txt.size() - 1)
            return 0;
        now++;
        return 1;
    } else if (com == home) {
        int t = 0;
        while (now > -1 && txt[now] != '\n')
            now--, t++;
        return t;
    } else if (com == en) {
        int t = 0;
        while (now + 1 != txt.size() && txt[now + 1] != '\n')
            now++, t++;
        return t;
    } else if (com == up) {
        auto col = move(home);
        move(le);
        move(home);
        while (col > 0 && now + 1 != txt.size() && txt[now + 1] != '\n')
            move(ri), col--;
    } else if (com == down) {
        auto col = move(home);
        move(en);
        if (!move(ri))
            move(home);
        while (col > 0 && now + 1 != txt.size() && txt[now + 1] != '\n')
            move(ri), col--;
    }
    return 0;
}
void insert(string c) {
    if (!selected) {
        txt.insert(now + 1, c);
        now += c.size();
    } else {
        int ks = min(now, remember) + 1, js = max(now, remember);
        txt.replace(ks, js - ks + 1, c);
        selected = false;
        now = ks + c.size() - 1;
    }
}
void remove(comd com) {
    if (!selected) {
        if (com == del) {
            if (now + 1 != txt.size())
                txt.erase(now + 1, 1);
        } else if (com == backspace)
            if (now != -1)
                txt.erase(now--, 1);
    } else {
        int ks = min(now, remember) + 1, js = max(now, remember);
        txt.erase(ks, js - ks + 1);
        selected = false;
        now = ks - 1;
    }
}
void find(string word) {
    int ks = 0, js = txt.size() - 1, cnt = 0, len = word.size();
    if (selected) {
        ks = min(now, remember) + 1;
        js = max(now, remember);
    }
    while (ks + len - 1 <= js)
        if (txt.substr(ks++, len) == word)
            cnt++;
    printf("%d\n", cnt);
}
void count() {
    int ks = 0, js = txt.size() - 1, cnt = 0;
    if (selected) {
        ks = min(now, remember) + 1;
        js = max(now, remember);
    }
    while (ks <= js) {
        if (txt[ks] != '\n' && txt[ks] != ' ')
            cnt++;
        ks++;
    }
    printf("%d\n", cnt);
}
void copy() {
    if (selected) {
        copyTxt = txt.substr(min(now, remember) + 1, abs(now - remember));
        haveCopy = true;
    } else {
        int saveNow = now;
        int ks = move(home), num = move(en);
        now = saveNow;
        if (num == 0)
            return;
        copyTxt = txt.substr(now - ks + 1, num);
        haveCopy = true;
    }
}
int n;
string op, wo, tmp;
void _() {
    cin >> n;
    FF(int, i, 1, n) {
        cin >> op;
        if (op == "MOVE") {
            cin >> wo;
            if (wo == "Home") {
                move(home);
            } else if (wo == "End") {
                move(en);
            } else if (wo == "Up") {
                move(up);
            } else if (wo == "Down") {
                move(down);
            } else if (wo == "Left") {
                move(le);
            } else if (wo == "Right") {
                move(ri);
            }
        } else if (op == "INSERT") {
            cin >> wo;
            if (wo == "Char") {
                cin >> tmp;
                insert(tmp);
            } else if (wo == "Enter") {
                insert("\n");
            } else if (wo == "Space") {
                insert(" ");
            } else if (wo == "Paste") {
                if (haveCopy)
                    insert(copyTxt);
            }
        } else if (op == "REMOVE") {
            cin >> wo;
            if (wo == "Del") {
                remove(del);
            } else
                remove(backspace);
        } else if (op == "SHIFT") {
            if (shifted) {
                shifted = false;
                if (remember != now)
                    selected = true;
            } else {
                shifted = true;
                if (selected) {
                    selected = false;
                } else
                    remember = now;
            }
        } else if (op == "FIND") {
            cin >> wo;
            find(wo);
        } else if (op == "COUNT") {
            count();
        } else if (op == "COPY") {
            copy();
        } else if (op == "PRINT") {
            cout << txt << '\n';
        }
    }
}
signed main() {
    // local;
    // cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _();
    return 0;
}
