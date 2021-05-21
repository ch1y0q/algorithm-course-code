#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 100005
#define INF 1000007

typedef long long ll;
using namespace std;

ll N, c[MAXN], y[MAXN];

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> N;
        rep(i, 1, N) { cin >> c[i]; }
        rep(i, 1, N) { cin >> y[i]; }

        ll ans = 0;
        rep(i, 1, N) {
            if (i > 1) c[i] = std::min(c[i], c[i - 1] + 1);
            ans += y[i] * c[i];
        }
        cout << ans << endl;
    }
    return 0;
}