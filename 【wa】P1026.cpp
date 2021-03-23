#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

int n, k;
int arr[25];

ll solve(int l, int r, int k) {  // [l, r]
    if (l == r) return arr[l];
    ll ans = 0;
    if (!k) {  // k = 0, all +
        for (int i = l; i <= r; ++i) {
            ans += arr[i];
        }
        return ans;
    }
    for (int i = l; i <= r; ++i) {
        for (int kk = 0; kk <= k; ++kk) {
            if (kk < i - l + 1 && k - 1 - kk < r - i) {
                ans = std::max(  // *
                    ans, solve(l, i, kk) * solve(i + 1, r, k - 1 - kk));
            }
            if (kk < i - l + 1 && k - kk < r - i) {
                ans = std::max(  // +
                    ans, solve(l, i, kk) + solve(i + 1, r, k - kk));
            }
        }
    }

    return ans;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        cout << solve(0, n - 1, k) << endl;
    }
    return 0;
}