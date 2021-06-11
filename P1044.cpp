#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")

#include <assert.h>

#include <algorithm>
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

using namespace std;

bool unused[MAXN];
double len[MAXN];
int O[MAXN];
int D[MAXN];
int order[MAXN];
int T, m, E, n;
vector<double> path[MAXN];

struct Edge
{
	Edge(int _u, int _v, double _w, double _t, double _alpha, int _index)
	{
		next = nullptr;
		t_0 = _t;
		alpha = _alpha;
		u = _u;
		v = _v;
		index = _index;
		weight = _w;
	}

	int index;
	double t_0;
	double alpha;
	int u;
	int v;
	double weight;
	Edge* next;
};

bool order_cmp(int x, int y) {
	return (O[x] < O[y]);
}

double Dijkstra(int u, int v, int qid, vector<Edge*> a, vector<Edge*> E)
{
	int t = v;
	vector<Edge*> p (m);
	for (int i = 0; i < m; i++)
	{
		p[i] = NULL;
		if (i == u){
			unused[i] = 0;
			len[i] = 0;
		}
		else{
			unused[i] = 1;
			len[i] = INF;
		}
	}

	Edge* tmp = a[u];
	int memo = u;
	while (unused[t] && t < m)
	{
		while (tmp)
		{
			tmp = tmp->next;
			if (tmp && unused[tmp->v])
			{
				double temp = len[memo] + tmp->weight;
				if (temp < len[tmp->v])
				{
					len[tmp->v] = temp;
					p[tmp->v] = tmp;
				}
			}
		}
		/* find edge with least len */
		double x = INF;
		int y = 0;
		for (int i = 0; i < m; i++)
		{
			if (unused[i])
			{
				if (len[i] <= x)
				{
					x = len[i];
					y = i;
				}
			}
		}
		tmp = a[y];
		memo = y;
		unused[y] = 0;
	}
	double an = len[t];

	while (p[t] && t < m)
	{
		if (path[qid].empty())
		{
			path[qid].push_back(p[t]->v);
			path[qid].push_back(p[t]->index);
			path[qid].push_back(p[t]->u);
		}
		else
		{
			path[qid].push_back(p[t]->index);
			path[qid].push_back(p[t]->u);
		}
		p[t] -> weight += (p[t]->t_0) * p[t]->alpha;  //update edge weight
		t = p[t]->u;
	}
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> m >> E >> n;	// #nodes, #edges, #queries

		/* init variables */
		vector<Edge*> a(m);
		vector<Edge*> edges(2 * E);
		rep(i, 0, n - 1) { path[i].clear(); }
		rep(i, 0, m - 1) { a[i] = new Edge(i, 0, 0, 0, 0, -1); }

		rep(i, 0, n - 1) { cin >> O[i] >> D[i]; }

		rep(i, 0, E - 1)
		{
			int u, v;
			double t0, al1, al2;
			cin >> u >> v >> t0 >> al1 >> al2;
			double w1 = t0 * (1 + al1);
			double w2 = t0 * (1 + al2);
			edges[2 * i] = new Edge(u, v, w1, t0, al1, 2 * i);
			edges[2 * i + 1] = new Edge(v, u, w1, t0, al2, 2 * i + 1);
			auto* tmp = a[u];
			while (tmp->next) {
				tmp = tmp->next;
			}
			tmp->next = edges[2 * i];
			tmp = a[v];
			while (tmp->next) {
				tmp = tmp->next;
			}
			tmp->next = edges[2 * i + 1];
		}

		rep(i, 0, n - 1)order[i] = i;
		//sort(order, order + n, order_cmp);
		random_shuffle(order, order + n);

		rep(i, 0, n - 1) {
			Dijkstra(O[order[i]], D[order[i]], order[i], a, edges);
		}
		rep(i, 0, n - 1) {
			cout << path[i].size() << endl;
			for (auto _ = path[i].crbegin(); _ != path[i].crend(); ++_)cout << *_ << " ";;
			cout << endl;
			path[i].clear();
		}
	}
	return 0;
}