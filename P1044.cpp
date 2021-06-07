#define MAGIC 0.00491
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXM 405
#define MAXE 10005
#define MAXN 8005
#define INF 1e7
using namespace std;

int n, E, s, t, m;
int u, v, w;

struct edge {
    int v;
    double t0;
    double alpha;
    int fe;  // count of vehicles on the edge
    int no;  // number of edge
    bool operator<(const edge& in) {
        return (t0 == in.t0) ? (alpha < in.alpha) : (t0 < in.t0);
    }
};

std::vector<edge> arr[MAXM];               // adjacent list
std::vector<std::pair<int, int>> queries;  // queries (s, t)

bool vis[MAXM];          // Dijkstra
double dis[MAXM];        // Dijkstra and Floyd
double map[MAXM][MAXM];  // Floyd
int P[MAXM][MAXM];       // Floyd
int map_no[MAXM][MAXM];  // Floyd; store edge #

string ans_str;
int ans_cnt;

/*
void Dijkstra() {
    while (true) {
        pair<double, int> p = make_pair(INF, -1); // <dis[i], i>
        rep(j, 1, n) {
            if (!vis[j]) p = std::min(p, make_pair(dis[j], j));
        }
        if (p.second == -1) { // all visited, return
            return;
        }
        vis[p.second] = true;
        for (auto it : arr[p.second]) {
            dis[it.v] = std::min(dis[it.v], dis[p.second] + it.t0);
        }
    }
}
*/

void Path(int u, int v) {
    if (P[u][v] == -1) {
        if (map_no[u][v] != -1) {
            ans_str = ans_str + to_string(map_no[u][v]) + ' ';
            ans_cnt++;
        }
        return;
    }
    Path(u, P[u][v]);
    ans_str += (to_string(P[u][v]) + ' ');
    ans_cnt++;
    Path(P[u][v], v);
    return;
}

void Floyd() {
    rep(k, 0, m - 1) {
        rep(i, 0, m - 1) {
            rep(j, 0, m - 1) {
                if (map[i][k] + map[k][j] < map[i][j]) {
                    map[i][j] = map[i][k] + map[k][j];  // update shortest
                                                        // length
                    P[i][j] = k;  // record intermediate point
                }
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> m >> E >> n;  // m: nodes; E: edges; n: queries

        /* init */
        queries.clear();
        rep(i, 0, m) {
            arr[i].clear();
            vis[i] = false;
            dis[i] = INF;
        }
        rep(i, 0, m) {
            rep(j, 0, m) {
                map[i][j] = INF;
                map_no[i][j] = -1;  // 0 is used as edge #
                P[i][j] = -1;       // 0 is used as vertex #
            }
        }

        /* read in */
        rep(i, 1, n) {
            int s, t;
            cin >> s >> t;
            queries.push_back(make_pair(s, t));
        }

        rep(i, 0, E - 1) {
            int u, v;
            double t0, alpha1, alpha2;
            cin >> u >> v >> t0 >> alpha1 >> alpha2;
            arr[u].push_back({v, t0, alpha1, 0, 2 * i});
            arr[v].push_back({u, t0, alpha2, 0, 2 * i + 1});

            map[u][v] = t0 + alpha1 / MAGIC;
            map[v][u] = t0 + alpha2 / MAGIC;
            map_no[u][v] = 2 * i;
            map_no[v][u] = 2 * i + 1;
        }

        /* solver */
        // dis[s] = 0;
        // Dijkstra();
        // cout << (dis[t] == INF ? -1 : dis[t]) << endl;
        Floyd();
        rep(i, 0, n - 1) {  // iterating queries
            int s = queries[i].first;
            int t = queries[i].second;
            ans_str = "";
            ans_cnt = 0;
            ans_str = to_string(s) + " ";
            ans_cnt++;
            Path(s, t);
            ans_str += to_string(t);
            ans_cnt++;

            cout << ans_cnt << endl;
            cout << ans_str << endl;
        }
    }
    return 0;
}