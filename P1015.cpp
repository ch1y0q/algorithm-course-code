#include <algorithm>
#include <iostream>
#include <string>

#define rep(i, j, k) for (int i = j; i <= k; ++i)
using namespace std;

int ans[10005];

int main() {
    int L = 1e7, R = 0, l, h, r, n;
    cin >> n;
    rep(i, 1, n) {
        cin >> l >> r >> h;
        L = min(L, l);
        R = max(R, r);
        rep(j, l, r - 1) ans[j] = max(ans[j], h);
    }
    rep(i, L, R - 1) {
        if (ans[i] != ans[i - 1]) cout << i << ' ' << ans[i] << endl;
    }
    cout << R << ' ' << 0 << endl;
    return 0;
}