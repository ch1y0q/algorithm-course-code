/*----------------------------------------------------------------
MinCMaxF
TLE. SPFA's fault?
------------------------------------------------------------------*/
#include <string.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define NEW_INDEX(y) y + n;
#define S_INDEX 0
#define T_INDEX n + m + 1
typedef long long ll;
using namespace std;

int const MAXN = 105;
int const MAXM = 505;
int const INF = INT_MAX;
int w[MAXN][MAXN];
int lx[MAXN], ly[MAXN];
int head[MAXN], cnt = 1;  // 这里特意把存图也贴出来，记住额外存一个参数c（费用）
struct Edge {
    int to, w, c, next;
} edges[MAXM * 2];
inline void add(int from, int to, int w, int c) {
    edges[++cnt].to = to;
    edges[cnt].w = w;
    edges[cnt].c = c;
    edges[cnt].next = head[from];
    head[from] = cnt;
}
int n, m, s, t, last[MAXN], flow[MAXN], inq[MAXN], dis[MAXN];
int maxflow, mincost;   // answers

queue<int> Q;
bool SPFA() {
    while (!Q.empty()) Q.pop();
    memset(last, -1, sizeof(last));
    memset(inq, 0, sizeof(inq));
    memset(dis, 127, sizeof(dis));
    flow[s] = INF;
    dis[s] = 0;
    Q.push(s);
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        inq[p] = 0;
        for (int eg = head[p]; eg != 0; eg = edges[eg].next) {
            int to = edges[eg].to, vol = edges[eg].w;
            if (vol > 0 && dis[to] > dis[p] + edges[eg].c)  // 容量大于0才增广
            {
                last[to] = eg;                   // 记录上一条边
                flow[to] = min(flow[p], vol);    // 更新下一个点的流量
                dis[to] = dis[p] + edges[eg].c;  // 注意这里是c不是w
                if (!inq[to]) {
                    Q.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    return last[t] != -1;
}


inline void MCMF()
{
    maxflow = mincost = 0;
    while (SPFA()) {
        maxflow += flow[t];
        mincost += dis[t] * flow[t];
        for (int i = t; i != s; i = edges[last[i] ^ 1].to) {
            edges[last[i]].w -= flow[t];
            edges[last[i] ^ 1].w += flow[t];
            //cout<<"last[i]"<<last[i]<<"\t flow "<<edges[last[i]].w<<endl;
        }
        //cout<<"flow[t] = "<<flow[t]<<endl;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        int x;  // cost of Girl i matching Boy j
        rep(i, 1, m) {
            rep(j, 1, n) {
                cin >> x;
                w[j][i] = x;
            }
        }
        int k;  // # of girls liked by Boy i

        rep(i, 1, n) {
            rep(i, 1, m) ly[i] = 0;
            cin >> k;
            rep(j, 1, k) {
                cin >> x;
                ly[x] = 1;
            }
            rep(j, 1, m) {
                if (ly[j]) {
                    int ww = w[i][j];
                    int t = NEW_INDEX(j);
                    add(i, t, 1, ww);
                    add(t, i, 0, -ww);
                }
            }
        }
        rep(i, 1, n) {
            add(S_INDEX, i, 1, 0);
            add(i, S_INDEX, 0, 0);
        }
        rep(j, 1, m) {
            int t = NEW_INDEX(j);
            add(t, T_INDEX, 1, 0);
            add(T_INDEX, t, 0, 0);
        }
        s = S_INDEX;
        t = T_INDEX;
        MCMF();
        cout << maxflow << " " << mincost << endl;
    }
    return 0;
}