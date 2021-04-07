#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (us a = b; a <= c; a++)
#define per(a, b, c) for (us a = b; a >= c; a--)
#define MAXN 10005

typedef long long ll;
typedef unsigned short us;
using namespace std;

struct point_pair {
    us i, j;
    us dis;
    bool operator<(const point_pair& toCmp) { return dis < toCmp.dis; }
};

us n, w[MAXN], b[MAXN]; /* position of ith white/black */
std::vector<point_pair> distances;
bool visW[MAXN], visB[MAXN];

void solve() {
    ll ans = 0;
    for (auto it : distances) {
        if (!visW[it.i] && !visB[it.j]) {
            ans += it.dis;
            visW[it.i] = visB[it.j] = true;
        }
    }
    cout << ans << endl;
}

int main() {
    us m;
    cin >> m;
    while (m--) {
        distances.clear();
        rep(i, 1, n) { visB[i] = visW[i] = false; }

        us white = 0, black = 0;
        cin >> n;
        rep(i, 1, 2 * n) {
            bool c;
            cin >> c;
            if (c) {
                b[++black] = i;
            } else {
                w[++white] = i;
            }
        }
        distances.reserve(n * n);
        //cout<<"sizeof "<<sizeof(distances)<< endl;
        rep(i, 1, n) {
            rep(j, 1, n) {
                distances.push_back(point_pair{i, j, (us)abs(w[i] - b[j])});
            }
        }
        sort(distances.begin(), distances.end());
        solve();
    }
    return 0;
}