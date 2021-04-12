/*----------------------------------------------------------------
二分图最佳匹配问题
KM算法
模板：https://blog.csdn.net/qq_40679299/article/details/81133478
https://www.cnblogs.com/Lanly/p/6291214.html
------------------------------------------------------------------*/
#include <string.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;

int const MAX = 505;
int const inf = INT_MAX;

int w[MAX][MAX];
int link[MAX];  //代表当前与Y集合中配对的X集合中的点
int visx[MAX], visy[MAX];
int lx[MAX], ly[MAX];
int n, m;  //代表X和Y中元素的个数

int can(int t) {
    visx[t] = 1;
    for (int i = 1; i <= m; i++) {
        if (!visy[i] &&
            lx[t] + ly[i] ==
                w[t]
                 [i]) {  //这里“lx[t]+ly[i]==w[t][i]”决定了这是在相等子图中找增广路的前提，非常重要
            visy[i] = 1;
            if (link[i] == -1 || can(link[i])) {
                link[i] = t;
                return 1;
            }
        }
    }
    return 0;
}

void km(void) {
    int sum = 0;
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= n; i++) {  //把各个lx的值都设为当前w[i][j]的最大值
        lx[i] = -inf;
        for (int j = 1; j <= m; j++) {
            if (lx[i] < w[i][j]) lx[i] = w[i][j];
        }
    }

    memset(link, -1, sizeof(link));
    for (int i = 1; i <= n; i++) {
        while (true) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if (can(i))  //如果它能够形成一条增广路径，那么就break
                break;
            int d = inf;  //否则，后面应该加入新的边,这里应该先计算d值
            for (
                int j = 1; j <= n;
                j++)  //对于搜索过的路径上的XY点，设该路径上的X顶点集为S，Y顶点集为T，对所有在S中的点xi及不在T中的点yj
                if (visx[j])
                    for (int k = 1; k <= m; k++)
                        if (!visy[k]) d = min(d, lx[j] + ly[k] - w[j][k]);
            if (d == inf)
                return;  //找不到可以加入的边，返回失败（即找不到完美匹配）
            for (int j = 1; j <= n; j++)
                if (visx[j]) lx[j] -= d;
            for (int j = 1; j <= m; j++)
                if (visy[j]) ly[j] += d;
        }
    }
    int pair = 0;
    for (int i = 1; i <= m; i++)
        if (link[i] > -1) sum += w[link[i]][i], pair++;
    cout << pair << " " << -sum << endl;
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
                w[j][i] = -x;
            }
        }
        int k;  // # of girls liked by Boy i
        rep(i, 1, m) ly[i] = 0;
        rep(i, 1, n) {
            cin >> k;
            rep(j, 1, k) {
                cin >> x;
                ly[x] = 1;
            }
            rep(j, 1, m) {
                if (!ly[j]) w[i][j] = 0;
            }
        }
        km();
    }
    return 0;
}