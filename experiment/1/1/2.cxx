#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string s;
    cin >> s;

    for (int i = 0; i + 1 < s.length(); ++i)
        if (s[i] == s[i + 1])
        {
            cout << "yes" << endl;
            return;
        }

    set<char> seen;
    bool has_upper = false;
    for (char c : s)
    {
        seen.insert(tolower(c));
        if (isupper(c))
            has_upper = true;
    }

    if (seen.size() < 26)
    {
        cout << "yes" << endl;
        return;
    }
    if (!has_upper)
    {
        cout << "yes" << endl;
        return;
    }
    cout << "no" << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
