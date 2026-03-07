#include <bits/stdc++.h>
using namespace std;
pair<int, int> ans = {0, 1e5 + 100};
signed
main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int cost;
        cin >> cost;
        string s;
        cin >> s;
        int c0 = 0, c1 = 0, c5 = 0;
        for (char c : s)
            if (c == '0')
                c0++;
            else if (c == '1')
                c1++;
            else if (c == '5')
                c5++;
        if (c0 >= 2 && c1 >= 1 && c5 >= 1)
            ans = cost < ans.second ? make_pair(i, cost) : ans;
    }
    cout << ans.first << endl;
}
