// by wcp
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#define MAXN 50007

typedef long long ll;
using namespace std;

int n, m;

struct job {
    int d, p;
    bool operator<(const job& toCmp) {
        if (d == toCmp.d)
            return p > toCmp.p;
        else
            return d < toCmp.d;
    }
} jobs[MAXN];

int main() {
    cin >> m;
    while (m--) {
        cin >> n;
        int maxd = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> jobs[i].d >> jobs[i].p;
            maxd = std::max(maxd, jobs[i].d);
        }
        sort(jobs + 1, jobs + n + 1);
        ll sum = 0;
        for (int i = maxd; i >= 1; --i) {
            int maxi = n;
            for (int j = n; j >= 1; --j) {
                if (jobs[j].d < i) break;
                if (jobs[j].p > jobs[maxi].p) maxi = j;
            }
            sum += jobs[maxi].p;
            jobs[maxi].p = 0;
        }
        cout << sum << endl;
    }
    return 0;
}