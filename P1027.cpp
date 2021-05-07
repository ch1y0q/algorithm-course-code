/* dp[i]=max(dp[j] + w[i])
    where s_i >= f_j;
          1 <= j < i */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 10007

typedef long long ll;
using namespace std;

struct job {
    int s = -1;
    int f = -1;
    int w = -1;
    bool operator<(const job& inJob) { return f < inJob.f; }
} jobs[MAXN];

int n;
int dp[MAXN];

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        rep(i, 0, n) { dp[i] = 0; }
        rep(i, 1, n) { cin >> jobs[i].s >> jobs[i].f >> jobs[i].w; }
        std::sort(jobs + 1, jobs + 1 + n);
        dp[1] = jobs[1].w;
        rep(i, 2, n) {
            int tt = jobs[i].w;
            rep(j, 1, i - 1) {
                if (jobs[i].s < jobs[j].f) break;
                tt = max(tt, dp[j] + jobs[i].w);
            }
            dp[i] = tt;
        }
        int tt = 0;
        rep(i, 1, n) { tt = max(tt, dp[i]); }
        cout << tt << endl;
    }
    return 0;
}