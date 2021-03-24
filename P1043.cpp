// https://leetcode-cn.com/problems/super-egg-drop/comments/35079
// https://www.jianshu.com/p/2f06a3eb953c

#include <algorithm>
#include <iostream>
#include <string>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;
int n, k;
int dp[105];  // dp[k][m] = dp[k-1][m-1] + dp[k][m-1] + 1

void solve() {
    int m = 0;
    for (int i = 0; i <= 104; ++i) {
        dp[i] = 0;
    }
    while (dp[k] < n) {
        m++;
        for (int K = k; K; --K) {
            dp[K] = dp[K] + dp[K - 1] + 1;
        }
    }
    cout << m << endl;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> k >> n;
        solve();
    }
    return 0;
}