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
struct Elements {
    string name;
    int num;
    Elements(string n1, int n2)
        : name(n1)
        , num(n2) {}
};
int number(string& str, int& i) {
    int num = 0;
    while (isdigit(str[i])) {
        num = num * 10 + str[i] - '0';
        i++;
    }
    return num;
}
bool judge(map<string, int>& mp1, map<string, int>& mp2) {
    if (mp1.size() != mp2.size())
        return false;
    for (map<string, int>::iterator it = mp1.begin(); it != mp1.end(); it++)
        if (mp2[it->first] != it->second)
            return false;
    return true;
}
void calculate(string& str, map<string, int>& mp) {
    stringstream ss(str);
    string item;
    while (getline(ss, item, '+')) {
        int factor = 1;
        int i = 0;
        vector<Elements> elements;
        if (isdigit(item[i]))
            factor = number(item, i);
        while (i < item.size()) {
            if (isdigit(item[i])) {
                int num = number(item, i);
                if (elements[elements.size() - 1].name == ")") {
                    int j = elements.size() - 1;
                    elements[j].name = "*";
                    while (elements[--j].name != "(")
                        elements[j].num *= num;
                    elements[j].name = "*";
                } else
                    elements[elements.size() - 1].num *= num;
            } else if (item[i] == '(') {
                elements.push_back(Elements("(", 0));
                i++;
            } else if (item[i] == ')') {
                elements.push_back(Elements(")", 0));
                if (i + 1 == item.size() || !isdigit(item[i + 1]))
                    item.insert(i + 1, "1");
                i++;
            } else if (isupper(item[i])) {
                string name = "";
                name += item[i];
                i++;
                if (islower(item[i])) {
                    name += item[i];
                    i++;
                }
                elements.push_back(Elements(name, 1));
            }
        }
        for (int j = 0; j < elements.size(); j++) {
            if (elements[j].name == "*")
                continue;
            mp[elements[j].name] += elements[j].num * factor;
        }
    }
}
string str, str_left, str_right;
void _() {
    cin >> str;
    stringstream ss(str);
    getline(ss, str_left, '=');
    getline(ss, str_right);
    map<string, int> left, right;
    calculate(str_left, left);
    calculate(str_right, right);
    if (judge(left, right))
        cout << "Y" << endl;
    else
        cout << "N" << endl;
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
