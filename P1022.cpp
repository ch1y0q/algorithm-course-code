#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int f[505][505];
string s, t;

int solve(int l, int r) {  //[l,r]
    if (l <= 0 || r <= 0) {
        return 0;
    }
    if (s[l - 1] == t[r - 1]) {  // 1<=l<=s.length()
        if (f[l - 1][r - 1] < 0) f[l - 1][r - 1] = solve(l - 1, r - 1);
        f[l][r] = f[l - 1][r - 1] + 1;
        return f[l][r];
    } else {
        if (f[l - 1][r] < 0) f[l - 1][r] = solve(l - 1, r);
        if (f[l][r - 1] < 0) f[l][r - 1] = solve(l, r - 1);
        f[l][r] = std::max(f[l][r], std::max(f[l - 1][r], f[l][r - 1]));
        return f[l][r];
    }
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> s >> t;
        for (int i = 1; i <= s.length(); ++i) {
            for (int j = 1; j <= t.length(); ++j) {
                f[i][j] = -1;
            }
        }
        cout << solve(s.length(), t.length()) << endl;
    }
    return 0;
}