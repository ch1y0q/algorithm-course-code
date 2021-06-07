#define MAGIC 0.00491
#define MAX_ITER 10
#define ITERATION_COEFF 0.003
#include <assert.h>

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
    // int fe;  // count of vehicles on the edge
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

int fe[MAXE];
double alpha[MAXM][MAXM];
double t0[MAXM][MAXM];

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

void Path_dumb(int u, int v) {  // no stdout output, count flow for each edge
    if (P[u][v] == -1) {
        if (map_no[u][v] != -1) {
            fe[map_no[u][v]]++;
        }
        return;
    }
    Path_dumb(u, P[u][v]);
    Path_dumb(P[u][v], v);
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
        /*
        rep(i, 0, m) {
            arr[i].clear();
            vis[i] = false;
            dis[i] = INF;
        }
        */
        rep(i, 0, m) {
            rep(j, 0, m) {
                map[i][j] = INF;
                map_no[i][j] = -1;  // edge # starting from 0
                P[i][j] = -1;       // vertex # starting from 0
                t0[i][j] = 0;
                alpha[i][j] = alpha[j][i] = 0;
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
            double t_0, alpha1, alpha2;
            cin >> u >> v >> t_0 >> alpha1 >> alpha2;
            // arr[u].push_back({v, t_0, alpha1, 2 * i});
            // arr[v].push_back({u, t_0, alpha2, 2 * i + 1});

            t0[u][v] = t0[v][u] = t_0;
            map[u][v] = t_0 + alpha1 / MAGIC;
            map[v][u] = t_0 + alpha2 / MAGIC;
            alpha[u][v] = alpha1;
            alpha[v][u] = alpha2;
            map_no[u][v] = 2 * i;
            map_no[v][u] = 2 * i + 1;
        }

        /* solver */
        // dis[s] = 0;
        // Dijkstra();
        // cout << (dis[t] == INF ? -1 : dis[t]) << endl;
        Floyd();
        int iter = 0;
        do {
            iter++;
            rep(i, 0, E) { fe[i] = 0; }
            rep(i, 0, n - 1) {  // iterating queries
                int s = queries[i].first;
                int t = queries[i].second;

                Path_dumb(s, t);  // get flow of each edge
            }

            /* modify map */
            rep(i, 0, m - 1) {
                rep(j, 0, m - 1) {
                    if (map_no[i][j] != -1) {
                        map[i][j] =
                            t0[i][j] + t0[i][j] * max(0, fe[map_no[i][j]] - 1) *
                                           alpha[i][j] * ITERATION_COEFF / iter;
                    } else {
                        map[i][j] = INF;
                    }
                }
            }

            /* get ready for next Floyd */
            rep(i, 0, m) {
                rep(j, 0, m) {
                    P[i][j] = -1;  // 0 is used as vertex #
                }
            }
            Floyd();

            // cout << iter << "************" << endl;
            // rep(i, 0, m - 1) {rep(j, 0, m - 1) cout << P[i][j] << " ";cout <<
            // endl; } cout << endl << "*****************" << endl;
        } while (iter < MAX_ITER);
        rep(i, 0, n - 1) {  // iterating queries: last time
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