#include <bits/stdc++.h>
using namespace std;
signed main() {
    set<char> s;
    char c;
    while (cin >> c)
        s.insert(c);
    cout << (s.size() == 1 ? "Won" : "Lost") << endl;
}
