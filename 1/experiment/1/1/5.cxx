#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        int sum = a + b + c;
        if (sum % 9 != 0)
            cout << "NO" << endl;
        else {
            int k = sum / 9;
            if (min({a, b, c}) < k)
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }
    }
    return 0;
}
