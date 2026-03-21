#include <bits/stdc++.h>
using namespace std;
signed main()
{
    int x, score = 0, res = 0;
    while (1)
    {
        cin >> x;
        if (!x)
            break;
        if (1 == x)
            score = 1;
        else
        {
            if (score == 0 || score == 1)
                score = 2;
            else
                score += 2;
        }
        res += score;
    }
    cout << res << "\n";

    return 0;
}
