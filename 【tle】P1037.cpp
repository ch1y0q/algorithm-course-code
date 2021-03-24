#include <algorithm>
#include <iostream>
#include <string>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;

int n, m, k;
int like[55][55];
bool liked[55];
int ans;
void solve(int s, int t) {
    if (s > n) {
        ans = std::max(ans, t);
        return;
    }
    rep(i, 1, like[s][0]) {
        if (!liked[like[s][i]]) {
            liked[like[s][i]] = true;
            solve(s + 1, t + 1);
            liked[like[s][i]] = false;
        }
    }
    solve(s + 1, t);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        ans = 0;
        rep(i, 0, 54) { rep(j, 0, 54) like[i][j] = 0; }  // init like[][]
        rep(i, 0, 54) { liked[i] = 0; }                  // init liked[]
        cin >> n >> m;
        rep(i, 1, n) {
            cin >> k;
            like[i][0] = k;
            rep(j, 1, k) { cin >> like[i][j]; }
        }
        solve(1, 0);
        cout << ans << endl;
    }
    return 0;
}