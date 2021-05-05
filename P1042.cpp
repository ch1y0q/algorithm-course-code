#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define INF 1e7

using namespace std;
int costs[3], m;
int days[370], f[370];
const int len[] = {1, 7, 30};

typedef long long ll;

// dp, good!
void solve() {
    int dc = 1;
    rep(i, 1, 365) {
        if (days[dc] != i) {
            f[i] = f[i - 1];
        } else {
            dc++;
            f[i] = f[i - 1] + costs[0];
            rep(k, 0, 2) {
                int t = i - len[k];
                if (t >= 1)
                    f[i] = min(f[i], f[t] + costs[k]);
                else {
                    f[i] = min(f[i], costs[k]);
                }
            }
        }
    }
    cout << f[365] << endl;
}

int main() {
    int nums;
    cin >> nums;
    while (nums--) {
        rep(i, 0, 365) { f[i] = days[i] = 0; }

        cin >> m;
        rep(i, 1, m) { cin >> days[i]; }
        rep(i, 0, 2) { cin >> costs[i]; }

        solve();
    }
    return 0;
}