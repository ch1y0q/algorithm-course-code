#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector> 
#include <queue>
#include <cstring>

#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define NEW_INDEX(y) y + n
#define S_INDEX 0
#define T_INDEX n + m + 1
#define INF 1e7

using namespace std;
const int maxn = 505;
typedef long long ll;
int d[maxn];
bool inq[maxn];
int p[maxn]; queue<int> q;
int n, m, s, t, w[maxn][maxn];

struct Edge { int from, to, flow, cap, cost; };
vector<Edge> edges;
vector<int> g[maxn];

void add(int from, int to, int cap, int cost) {
	edges.push_back(Edge{ from, to, 0, cap, cost });
	g[from].push_back(edges.size() - 1);
	edges.push_back(Edge{ to, from, 0, 0, -cost });
	g[to].push_back(edges.size() - 1);
	return;
}

bool bfs() {
	rep(i, 0, maxn - 1)d[i] = INF;
	memset(inq, 0, sizeof(inq));
	q.push(s); d[s] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		inq[x] = false;
		for (int i = 0; i < g[x].size(); i++) {
			Edge e = edges[g[x][i]];
			if (e.cap == e.flow)continue;
			int y = e.to;
			if (d[y] > d[x] + e.cost) {
				d[y] = d[x] + e.cost;
				p[y] = g[x][i];
				if (!inq[y])q.push(y);
				inq[y] = true;
			}
		}
	}
	if (d[t] == INF)return 0;
	return 1;
}
void mincost() {
	int flow = 0, f;
	ll cost = 0, tot;
	while (bfs()) {
		f = INF; tot = 0;
		for (int i = t; i != s; i = edges[p[i]].from) {
			Edge e = edges[p[i]];
			f = min(f, e.cap - e.flow);
			tot += e.cost;
		}
		flow += f;
		cost += tot * f;
		for (int i = t; i != s; i = edges[p[i]].from) {
			edges[p[i]].flow += f;
			edges[p[i] ^ 1].flow -= f;
		}
	}
	cout << flow << " " << cost << endl;
	return;
}

int main()
{
	int T;
	cin >> T;
	while (T--) {
		/* init */
		edges.clear();
		for (int i = 0; i < maxn; i++) {
			g[i].clear();
		}

		cin >> n >> m;

		s = S_INDEX;
		t = T_INDEX;

		rep(i, 1, m) {
			rep(j, 1, n) { cin >> w[i][j]; }
		}
		rep(i, 1, n) {
			int k;  // # of girls liked by Boy i
			cin >> k;
			rep(j, 1, k) {
				int x;
				cin >> x;
				add(i, NEW_INDEX(x), 1, w[x][i]);
			}
		}
		rep(i, 1, n) {
			add(s, i, 1, 0);
			// add(i, S_INDEX, 0, 0);
		}
		rep(j, 1, m) {
			add(NEW_INDEX(j), t, 1, 0);
			// add(T_INDEX, t, 0, 0);
		}
		mincost();
	}
}
