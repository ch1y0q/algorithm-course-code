#define fastcall __attribute__((optimize("-O3")))
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <assert.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define INF 1e7
#define MAXM 405
#define MAXE 10005
#define MAXN 8005
#define MAGIC 0.00491
#define RPROB 7
#define MAX_ITER 12
#define FACTOR 0.1

using namespace std;

bool vis[MAXN];
double dis[MAXN];

int O[MAXN];
int D[MAXN];
int order[MAXN];
double tot_cost[MAXN];

int T, m, E, n;
int u, v;
double t0, alpha1, alpha2;

struct Edge {
    Edge(int _u, int _v, double _w, double _t, double _alpha, int _index,
         Edge* _next)
        : u(_u),
          v(_v),
          weight(_w),
          t_0(_t),
          alpha(_alpha),
          index(_index),
          next(_next) {}
    Edge(int _u, int _v, double _w, double _t, double _alpha, int _index)
        : Edge(_u, _v, _w, _t, _alpha, _index, nullptr) {}
    int u;
    int v;
    double weight;
    double t_0;
    double alpha;
    int index;
    Edge* next;
};

vector<int> path[MAXN];
vector<Edge*> edges(2 * MAXE, nullptr);

inline bool order_cmp(int x, int y) { return (O[x] < O[y]); }

inline bool w_cmp(int x, int y) { return (tot_cost[O[x]] > tot_cost[O[y]]); }

void Dijkstra(int u, int v, int qid, vector<Edge*>& adj) {
    int t = v;
    vector<Edge*> p(m, nullptr);

    /* prepare for Dijkstra */
    rep(i, 0, m - 1) {
        vis[i] = (i == u);
        dis[i] = (i != u ? INF : 0);
    }

    Edge* cur_edge = adj[u];
    int cur_vertex = u;
    while (!vis[t] && t < m) {
        while (cur_edge) {
            cur_edge = cur_edge->next;
            if (cur_edge && !vis[cur_edge->v]) {
                double temp = dis[cur_vertex] + cur_edge->weight;
                if (temp < dis[cur_edge->v]) {
                    dis[cur_edge->v] = temp;
                    p[cur_edge->v] = cur_edge;
                }
            }
        }

        /* find edge with least dis */
        double t_dis = INF;
        int t_node = 0;
        rep(i, 0, m - 1) {
            if (!vis[i] && dis[i] <= t_dis) {
                t_dis = dis[i];
                t_node = i;
            }
        }
        cur_edge = adj[t_node];
        cur_vertex = t_node;
        vis[t_node] = true;
    }

    path[qid].push_back(p[t]->v);  // push back destination
    while (p[t] && t < m) {
        assert(p[t]->index >= 0);
        path[qid].push_back(p[t]->index);
        path[qid].push_back(p[t]->u);

        tot_cost[qid] *=
            p[t]->weight / p[t]->t_0;  // update tot_cost of the query
        p[t]->weight += (p[t]->t_0) * p[t]->alpha;  // update edge weight
        t = p[t]->u;
    }
    // path is stored in reverse order
}

int main() {
    srand(time(NULL));
    cin >> T;
    while (T--) {
        for (auto ptr : edges) {
            if (ptr != nullptr) delete ptr;
        }
        edges.clear();

        cin >> m >> E >> n;  // #nodes, #edges, #queries

        /* init variables */
        vector<Edge*> adj(m, nullptr);
        // rep(i, 0, n - 1) { path[i].clear(); }
        rep(i, 0, m - 1) { adj[i] = new Edge(i, 0, 0, 0, 0, -1); }
        rep(i, 0, n - 1) tot_cost[i] = 0;

        rep(i, 0, n - 1) { cin >> O[i] >> D[i]; }

        edges.reserve(2 * E);
        rep(i, 0, E - 1) {
            cin >> u >> v >> t0 >> alpha1 >> alpha2;
            edges.push_back(new Edge(u, v, t0, t0, alpha1, 2 * i));
            edges.push_back(new Edge(v, u, t0, t0, alpha2, 2 * i + 1));

            /* get adjacent list */
            auto* tmp = adj[u];
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = edges[2 * i];
            tmp = adj[v];
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = edges[2 * i + 1];
        }

        rep(i, 0, n - 1) order[i] = i;
        /*sort(order, order + n, order_cmp);*/
        std::random_shuffle(order, order + n);

        rep(i, 0, n - 1) { Dijkstra(O[order[i]], D[order[i]], order[i], adj); }

        rep(_, 1, MAX_ITER) {
            std::partial_sort(order, order + (int)ceil(n * FACTOR), order + n,
                              w_cmp);
            // sort(order, order + n, w_cmp);
            rep(i, 0, n * FACTOR) {
                tot_cost[i] = 0;
                for (auto it = path[order[i]].begin() + 1;
                     it < path[order[i]].end(); it += 2) {
                    int edge_no = *it;
                    edges[edge_no]->weight -=
                        edges[edge_no]->t_0 * edges[edge_no]->alpha;
                }
                path[order[i]].clear();
                Dijkstra(O[order[i]], D[order[i]], order[i], adj);
            }

            rep(i, 0, n - 1) {
                if (rand() % RPROB) continue;
                tot_cost[i] = 0;
                for (auto it = path[order[i]].begin() + 1;
                     it < path[order[i]].end(); it += 2) {
                    int edge_no = *it;
                    edges[edge_no]->weight -=
                        edges[edge_no]->t_0 * edges[edge_no]->alpha;
                }
                path[order[i]].clear();
                Dijkstra(O[order[i]], D[order[i]], order[i], adj);
            }
        }

        rep(i, 0, n - 1) {
            cout << path[i].size() << endl;
            // cout << O[i] << " ";
            for (auto it = path[i].crbegin(); it != path[i].crend(); ++it) {
                // int edge_no = *it;
                // cout << edge_no << " " << edges[edge_no]->v << " ";
                cout << *it << " ";
            }
            cout << endl;
            path[i].clear();
        }
    }
    return 0;
}