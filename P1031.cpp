#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define eps 1e-10
#define MAXN 10005
typedef long long ll;
using namespace std;

struct point {
    int x, y;
    double d;
    bool operator<(const point& toCmp) { return x + d < toCmp.x + toCmp.d; }
} points[MAXN];

vector<double> pos;

int n, d, x, y;

void solve() {
    rep(i, 1, n) {
        auto p = points[i];
        if (!pos.empty() && pos.back() >= p.x - p.d - eps &&
            pos.back() <= p.x + p.d + eps) {
            continue;
        } else {
            pos.push_back(p.x + p.d);
        }
    }
    cout << pos.size() << endl;
    // for (auto i : pos) cout << i << "\t";
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        pos.clear();
        cin >> n >> d;
        rep(i, 1, n) {
            cin >> x >> y;
            points[i].x = x;
            points[i].y = y;
            points[i].d = sqrt(d * d - y * y);
        }
        sort(points + 1, points + 1 + n);
        solve();
    }
    return 0;
}