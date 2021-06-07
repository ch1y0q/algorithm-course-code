#define MAGIC 0.00491
#define MAX_ITER 10

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
int u, v;

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

std::vector<std::pair<int, int>> queries;  // queries (s, t)

double map[MAXM][MAXM];  // Floyd
int P[MAXM][MAXM];       // Floyd
int map_no[MAXM][MAXM];  // Floyd; store edge #

int fe[MAXE];
double alpha[MAXM][MAXM];
double t0[MAXM][MAXM];

string ans_str;
int ans_cnt;

inline double w(int u, int v) {
    return t0[u][v] + 2 * t0[u][v] * alpha[u][v] * fe[map_no[u][v]];
}

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

void Floyd_init() {
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

void Floyd() {
    rep(k, 0, m - 1) {
        rep(i, 0, m - 1) {
            rep(j, 0, m - 1) {
                if (map_no[i][k] < 0 || map_no[k][j] < 0) continue;
                assert(map[i][j] != INF);
                int w_ = w(i, k) + w(k, j);
                if (w_ < map[i][j]) {  // relax
                    map[i][j] = w_;    // update shortest
                                       // length
                    P[i][j] = k;       // record intermediate point
                    P[i][k] = -1;
                    P[k][j] = -1;
                    fe[map_no[i][k]]++;
                    fe[map_no[k][j]]++;
                    fe[map_no[i][j]]--;
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

            t0[u][v] = t0[v][u] = t_0;
            map[u][v] = t_0 + alpha1 / MAGIC;
            map[v][u] = t_0 + alpha2 / MAGIC;
            alpha[u][v] = alpha1;
            alpha[v][u] = alpha2;
            map_no[u][v] = 2 * i;
            map_no[v][u] = 2 * i + 1;
        }

        /* solver */
        // init
        rep(i, 0, E) { fe[i] = 0; }
        rep(i, 0, m) {
            rep(j, 0, m) {
                P[i][j] = -1;  // 0 is used as vertex #
            }
        }
        Floyd_init();
        rep(i, 0, n - 1) {  // iterating queries: last time
            int s = queries[i].first;
            int t = queries[i].second;
            Path_dumb(s, t);
        }

        int iter = 0;
        do {
            iter++;
            Floyd();
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