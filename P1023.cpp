#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 505
#define MAXE 10005
#define INF 1e7
using namespace std;

int n, E, s, t, M;
int pass[MAXN];
int u, v, w;
std::vector<std::pair<int, int>>
    arr[MAXN]; /* arr[u] = {<v1, w1>, <v2, w2>, ..,} */
bool vis[MAXN];
int f[MAXN][MAXN];

int dp(int i, int j) {  // go to i, money j left in pocket
    if (f[i][j] >= 0) return f[i][j];
    f[i][j] = INF;
    if (j < pass[i]) return f[i][j];
    if (i == s) {
        f[i][j] = 0;
        return 0;
    }
    vis[i] = true;
    for (auto &edge : arr[i]) {
        if (vis[edge.first]) continue;
        int tt = dp(edge.first, j - pass[i]);  // return INF if no money
        tt = (tt == INF ? INF : tt + edge.second);
        f[i][j] = min(f[i][j], tt);
    }
    vis[i] = 0;
    return f[i][j];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> E >> s >> t >> M;
        rep(i, 1, n) {
            arr[i].clear();
            vis[i] = false;
        }
        memset(f, -1, sizeof(f));
        rep(i, 1, n) { cin >> pass[i]; }
        pass[s] = 0;
        rep(i, 1, E) {
            cin >> u >> v >> w;
            arr[u].push_back(make_pair(v, w));  // u->v
            arr[v].push_back(make_pair(u, w));  // v->u
        }

        int ans = dp(t, M);
        cout << (ans == INF ? -1 : ans) << endl;
    }
    return 0;
}