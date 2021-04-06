#include <algorithm>
#include <iostream>
#include <string>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 100005
typedef long long ll;
int n, maxddl = -1;
bool checked[MAXN];
using namespace std;

struct job {
    int d, p;
    bool checked = false;
    bool operator<(const job& toCmp) {
        if (d == toCmp.d)
            return p > toCmp.p;
        else
            return d < toCmp.d;
    }
} jobs[MAXN];

void solve() {
    ll ans = 0;

    int j = 1;
    rep(i, 1, maxddl) {
        while ((jobs[j].checked || i > jobs[j].d) && j <= n) {
            j++;
        }
        // cout << "i " << i<< " j"<<j << endl;
        if (!jobs[j].checked && i <= jobs[j].d && j <= n) {
            ans += jobs[j].p;
            jobs[j].checked = true;
            // cout << "added " << j << endl;
            // jobs[ti].checked = true;
            // cout << "t " << t << "ti " << ti << endl;
        }
    }
    cout << ans << endl;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        maxddl = -1;
        rep(i, 1, n) {
            cin >> jobs[i].d >> jobs[i].p;
            jobs[i].checked = false;
            maxddl = std::max(maxddl, jobs[i].d);
        }
        std::sort(jobs + 1, jobs + n + 1);
        // rep(i, 1, n) cout << jobs[i].d << " " << jobs[i].p << " ";
        solve();
    }
    return 0;
}