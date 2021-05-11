
// MCMF Dinic algorithm: https://blog.csdn.net/aiwo1376301646/article/details/104300253
#include <bits/stdc++.h>

#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define NEW_INDEX(y) y + n
#define S_INDEX 0
#define T_INDEX n + m + 1

using namespace std;
const int maxn = 505, maxm = 1e5 + 1;
int w[maxn][maxn];
int n, m, s, t, tot = 1, head[maxn], dis[maxn], flow[maxn], pre[maxn],
                last[maxn], maxflow, mincost;
// dis最小花费;pre每个点的前驱；last每个点的所连的前一条边；flow源点到此处的流量
bool vis[maxn];
queue<int> q;

struct edge {
    int to, next, w, dis;  // w流量 dis花费
} e[maxm];

void add(int x, int y, int w, int dis) {
    e[++tot].to = y;
    e[tot].w = w;
    e[tot].dis = dis;
    e[tot].next = head[x];
    head[x] = tot;

    e[++tot].to = x;
    e[tot].w = 0;
    e[tot].dis = -dis;
    e[tot].next = head[y];
    head[y] = tot;
}

bool spfa(int s, int t) {
    memset(dis, 0x7f, sizeof(dis));
    memset(flow, 0x7f, sizeof(flow));
    memset(vis, 0, sizeof(vis));
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;
    pre[t] = -1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = e[i].next) {
            int y = e[i].to;
            if (e[i].w > 0 && dis[y] > dis[now] + e[i].dis)  //相当于求最短路
            {
                dis[y] = dis[now] + e[i].dis;
                pre[y] = now;
                last[y] = i;
                flow[y] = min(flow[now], e[i].w);
                if (!vis[y]) {
                    vis[y] = 1;
                    q.push(y);
                }
            }
        }
    }
    return pre[t] != -1;
}

void dfs() {
    int now = t;
    maxflow += flow[t];
    mincost += flow[t] * dis[t];
    while (now != s)  //从汇点一直回溯到源点
    {
        e[last[now]].w -= flow[t];
        e[last[now] ^ 1].w += flow[t];
        now = pre[now];
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
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
        while (spfa(s, t)) dfs();
        cout << maxflow << " " << mincost << endl;
    }
    return 0;
}