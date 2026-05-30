#include <bits/stdc++.h>
using namespace std;
int n, k, cnt;
map<int, int> mp;
signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    for (auto [x, y] : mp)
        if (y >= 2)
            cnt += y / 2;
    cout << cnt << endl;
}
