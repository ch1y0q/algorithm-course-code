#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 1007

typedef long long ll;
using namespace std;

int main() {
    int m, n;
    cin >> m;
    while (m--) {
        cin >> n;
        int x, ans = 0;
        rep(i, 1, n - 1) {
            cin >> x;
            ans += x;
        }
        cout << fixed << setprecision(6) << (1.0 + ans * 0.01) << endl;
    }
    return 0;
}