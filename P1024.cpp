#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;
double p[505], q[505], w[505][505], results[505][505];
int n, key[505];

double solve(int l, int r) {
    if (results[l][r] > 0) return results[l][r];
    if (r == l - 1) {
        return q[l - 1];
    }
    double t = 1e7;
    rep(i, l, r) {
        t = std::min(t, solve(l, i - 1) + solve(i + 1, r) + w[l][r]);
    }
    results[l][r] = t;
    return t;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        rep(i, 0, n) { rep(j, 0, n) w[i][j] = results[i][j] = 0; }
        double qsum = 0.0;
        cin >> n;
        rep(i, 1, n) { cin >> key[i]; }
        rep(i, 1, n) { cin >> p[i]; }
        rep(i, 0, n) {
            cin >> q[i];
            qsum += q[i];
        }
        rep(i, 1, n) {
            w[i][i - 1] = q[i - 1];
            rep(j, i, n) w[i][j] = w[i][j - 1] + p[j] + q[j];
        }
        // rep(i, 0, n) { rep(j, 0, n) cout<<w[i][j]<<'\t';cout<<endl; }

        cout << fixed << setprecision(6) << solve(1, n) - qsum << endl;
    }
    return 0;
}