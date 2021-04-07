#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (us a = b; a <= c; a++)
#define per(a, b, c) for (us a = b; a >= c; a--)
#define MAXN 20005

typedef long long ll;
typedef unsigned short us;
using namespace std;

int n;
bool p[MAXN], vis[MAXN];

void solve() {
    ll ans = 0;
    rep(i, 1, 2 * n) {
        if (!vis[i]) {
            rep(j, i + 1, 2 * n) {
                if (!vis[j] && p[j] != p[i]) {
                    vis[j] = vis[i] = true;
                    ans += (j - i);
                    break;
                }
            }
        }
    }
    cout << ans << endl;
}

int main() {
    us m;
    cin >> m;
    while (m--) {
        cin >> n;
        rep(i, 1, 2 * n) {
            cin >> p[i];
            vis[i] = false;
        }
        solve();
    }
    return 0;
}