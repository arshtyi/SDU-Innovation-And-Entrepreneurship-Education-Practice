#include <bits/stdc++.h>
using namespace std;
int n, r, g, b;
int main() {
    cin >> n;
    char c;
    while (cin >> c)
        if (c == 'R')
            r++;
        else if (c == 'G')
            g++;
        else if (c == 'B')
            b++;
    cout << min({r, g, b}) << endl;
    return 0;
}
