#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    int ma = v[n - 1];
    int mi = v[0];
    if (n % 2) {
        int mid = v[n / 2];
        cout << ma << " " << mid << " " << mi << endl;
    } else {
        if ((v[n / 2] + v[n / 2 - 1]) % 2 == 0) {
            int mid = (v[n / 2] + v[n / 2 - 1]) / 2;
            cout << ma << " " << mid << " " << mi << endl;
        } else {
            double mid = (v[n / 2] + v[n / 2 - 1]) / 2.0;
            cout << ma << " ";
            cout << fixed << setprecision(1) << mid << " ";
            cout << mi << endl;
        }
    }

    return 0;
}
