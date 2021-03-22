#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n;
int row[505], col[505];
int f[505][505];

int solve(int l, int r) {  //[l,r]
    if (l >= r) {
        return 0;
    }
    int ans = 1e7;
    for (int i = l; i < r; ++i) {
        int a = f[l][i], b = f[i + 1][r];
        if (a < 0) a = solve(l, i);
        if (b < 0) b = solve(i + 1, r);
        ans = std::min(ans, a + b + row[l] * col[i] * col[r]);
    }
    f[l][r] = ans;
    return ans;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> row[i] >> col[i];
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                f[i][j] = -1e7;
            }
        }
        cout << solve(1, n) << endl;
    }
    return 0;
}