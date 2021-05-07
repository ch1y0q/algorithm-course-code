#include <algorithm>
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
int dis[MAXN];

void Dijkstra() {
    while (true) {
        pair<int, int> p = make_pair(INF, -1); /* <dis[i], i> */
        rep(j, 1, n) {
            if (!vis[j]) p = std::min(p, make_pair(dis[j], j));
        }
        if (p.second == -1) { /* all visited, return */
            return;
        }
        vis[p.second] = true;
        for (auto it : arr[p.second]) {
            dis[it.first] = std::min(dis[it.first], dis[p.second] + it.second);
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> E >> s >> t >> M;
        rep(i, 1, n) {
            arr[i].clear();
            vis[i] = false;
            dis[i] = INF;
            pass[i] = 0;
        }
        rep(i, 1, n) { cin >> pass[i]; }
        rep(i, 1, E) {
            cin >> u >> v >> w;
            arr[u].push_back(make_pair(v, w));  // u->v
            arr[v].push_back(make_pair(u, w));  // v->u
        }
        dis[s] = 0;
        Dijkstra();
        cout << (dis[t] == INF ? -1 : dis[t]) << endl;
    }
    return 0;
}