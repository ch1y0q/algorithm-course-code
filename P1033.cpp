#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#define MAXN 50007
#define MAXD 1000007
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;

int n, m;
bool t[MAXD];

struct job {
    int d, p;
    bool operator<(const job& toCmp) { return p > toCmp.p; }
} jobs[MAXN];

bool judge(int ddl) {
    per(i, ddl, 1) {
        if (!t[i]) {
            return t[i] = true;
        }
    }
    return false;
}

int main() {
    cin >> m;
    while (m--) {
        cin >> n;
        int maxd = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> jobs[i].d >> jobs[i].p;
            maxd = std::max(maxd, jobs[i].d);
        }
        rep(i, 1, maxd) { t[i] = false; }
        sort(jobs + 1, jobs + n + 1);

        ll sum = 0;
        rep(i, 1, n) {
            if (judge(jobs[i].d)) {
                sum += jobs[i].p;
            }
        }
        cout << sum << endl;
    }
    return 0;
}