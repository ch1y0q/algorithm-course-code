#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int* l;
int* p;

void solve(int n, int k) {
    int *r = new int[n + 5], i, j;
    for (i = 0; i <= n; ++i) {
        r[i] = 0;
    }
    for (i = 0; i <= n; ++i) {
        for (j = 0; j < k; ++j) {
            if (i - l[j] < 0) {
                continue;
            } else {
                r[i] = std::max(r[i], r[i - l[j]] + p[j]);
            }
        }
    }
    cout << r[n] << endl;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        int n, k;
        cin >> n >> k;
        l = new int[k];
        p = new int[k];
        for (int i = 0; i < k; ++i) {
            cin >> l[i] >> p[i];
        }
        solve(n, k);
    }
    return 0;
}