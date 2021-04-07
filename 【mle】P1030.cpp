#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 10005

typedef long long ll;
using namespace std;

int n, w[MAXN], b[MAXN]; /* position of ith white/black */
std::vector<std::pair<int, std::pair<int, int>>> distances;
/* first: distances between ith white and jth black; second:<i, j> */
bool visW[MAXN], visB[MAXN];

void solve() {
    ll ans = 0;
    for (auto it : distances) {
        if (!visW[it.second.first] && !visB[it.second.second]) {
            ans += it.first;
            visW[it.second.first] = visB[it.second.second] = true;
        }
    }
    cout << ans << endl;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        distances.clear();
        rep(i, 1, n) { visB[i] = visW[i] = false; }

        int white = 0, black = 0;
        cin >> n;
        rep(i, 1, 2 * n) {
            int c;
            cin >> c;
            if (c) {
                b[++black] = i;
            } else {
                w[++white] = i;
            }
        }
        rep(i, 1, n) {
            rep(j, 1, n) {
                distances.push_back(
                    make_pair(abs(w[i] - b[j]), make_pair(i, j)));
            }
        }
        sort(distances.begin(), distances.end());
        solve();
    }
    return 0;
}