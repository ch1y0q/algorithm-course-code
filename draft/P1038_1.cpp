#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define INF 0x3f3f3f3f

#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define NEW_INDEX(y) y + n
#define S_INDEX 0
#define T_INDEX n + m + 1

using namespace std;
const int maxn = 505;

// MCMF 模板：https://blog.csdn.net/sugarbliss/article/details/89195128
bool vis[maxn];
int n, m, s, t, x, y, z, f, dis[maxn], pre[maxn], last[maxn], flow[maxn],
    maxflow, mincost;
int w[maxn][maxn], lx[maxn], ly[maxn];
// dis最小花费;pre每个点的前驱；last每个点的所连的前一条边；flow源点到此处的流量
struct node {
    int next, to, flow, dis;
} edge[maxn];  // flow流量 dis花费
int head[maxn], cnt;
queue<int> q;

void add(int u, int v, int flow, int dis) {
    edge[cnt] = (node){head[u], v, flow, dis};
    head[u] = cnt++;
    edge[cnt] = (node){head[v], u, 0, -dis};
    head[v] = cnt++;
    //反边的流量为0，花费是相反数
}

bool spfa(int s, int t) {
    for (int i = 0; i < t + 10; i++) dis[i] = INF, flow[i] = INF, vis[i] = 0;
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;
    pre[t] = -1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = edge[i].next) {
            if (edge[i].flow > 0 &&
                dis[edge[i].to] > dis[now] + edge[i].dis)  //正边
            {
                dis[edge[i].to] = dis[now] + edge[i].dis;
                pre[edge[i].to] = now;
                last[edge[i].to] = i;
                flow[edge[i].to] = min(flow[now], edge[i].flow);  //
                if (!vis[edge[i].to]) {
                    vis[edge[i].to] = 1;
                    q.push(edge[i].to);
                }
            }
        }
    }
    return pre[t] != -1;
}

void MCMF() {
    maxflow = 0, mincost = 0;
    while (spfa(s, t)) {
        int now = t;
        maxflow += flow[t];
        mincost += flow[t] * dis[t];
        while (now != s) {                    //从源点一直回溯到汇点
            edge[last[now]].flow -= flow[t];  // flow和dis容易搞混
            edge[last[now] ^ 1].flow += flow[t];
            now = pre[now];
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        memset(head, -1, sizeof(head));
        cnt = 0;  //初始化
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
        MCMF();
        cout << maxflow << " " << mincost << endl;
    }
    return 0;
}