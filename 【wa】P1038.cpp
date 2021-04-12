/*----------------------------------------------------------------
����ͼ���ƥ������
KM�㷨
ģ�壺https://blog.csdn.net/qq_40679299/article/details/81133478
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
int link[MAX];  //����ǰ��Y��������Ե�X�����еĵ�
int visx[MAX], visy[MAX];
int lx[MAX], ly[MAX];
int n, m;  //����X��Y��Ԫ�صĸ���

int can(int t) {
    visx[t] = 1;
    for (int i = 1; i <= m; i++) {
        if (!visy[i] &&
            lx[t] + ly[i] ==
                w[t]
                 [i]) {  //���lx[t]+ly[i]==w[t][i]�������������������ͼ��������·��ǰ�ᣬ�ǳ���Ҫ
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
    for (int i = 1; i <= n; i++) {  //�Ѹ���lx��ֵ����Ϊ��ǰw[i][j]�����ֵ
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
            if (can(i))  //������ܹ��γ�һ������·������ô��break
                break;
            int d = inf;  //���򣬺���Ӧ�ü����µı�,����Ӧ���ȼ���dֵ
            for (
                int j = 1; j <= n;
                j++)  //������������·���ϵ�XY�㣬���·���ϵ�X���㼯ΪS��Y���㼯ΪT����������S�еĵ�xi������T�еĵ�yj
                if (visx[j])
                    for (int k = 1; k <= m; k++)
                        if (!visy[k]) d = min(d, lx[j] + ly[k] - w[j][k]);
            if (d == inf)
                return;  //�Ҳ������Լ���ıߣ�����ʧ�ܣ����Ҳ�������ƥ�䣩
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