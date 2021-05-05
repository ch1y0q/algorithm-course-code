/*
dp[root][black]=
        sum(dp[child][white])

dp[root][white]=
        sum(max(dp[child][white], dp[child][black]))

dp[leaf][white]=0
dp[leaf][black]=1
*/

#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

#define MAXN 50005

typedef long long ll;
using namespace std;

int vis[MAXN], b[MAXN], w[MAXN];
vector<int> tree[MAXN];
int n;

void solve(int r) {
    vis[r] = 1;
    for (int edge : tree[r]) {
        if (vis[edge])
            continue;
        else {
            solve(edge);
        }
    }
    b[r] = 1;
    for (int edge : tree[r]) {
        b[r] += w[edge];
        w[r] += max(b[edge], w[edge]);
    }
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        rep(i, 0, n) {
            tree[i].clear();
            b[i] = w[i] = vis[i] = 0;
        }
        rep(i, 1, n - 1) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        solve(1);
        int ans = max(b[1], w[1]);
        cout << ans << endl;
    }
    return 0;
}