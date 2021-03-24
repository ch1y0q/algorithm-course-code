#include <iostream>
#include <string>
using namespace std;

typedef long long ll;
ll results[25][25][25];

int arr[25];

ll solve(int l, int r, int k) {  // [l, r]
    if (r - l < k) return -1e7;
    if (l == r) return arr[l];
    if (results[l][r][k] > 0) return results[l][r][k];
    if (k == 1) {
        ll ans = 0;
        for (int i = l; i < r; ++i) {
            ll left = 0, right = 0;
            for (int j = l; j <= i; ++j) {
                left += arr[j];
            }
            for (int j = i + 1; j <= r; ++j) {
                right += arr[j];
            }
            ans = std::max(ans, left * right);
        }
        return ans;
    }
    ll ans = 0;
    if (!k) {  // k = 0, all +
        for (int i = l; i <= r; ++i) {
            ans += arr[i];
        }
        return ans;
    }
    for (int i = l; i < r; ++i) {
        for (int kk = 0; kk <= k; ++kk) {
            if (kk <= i - l && k - 1 - kk <= r - (i + 1) && k - 1 - kk >= 0) {
                ans = std::max(  // *
                    ans, solve(l, i, kk) * solve(i + 1, r, k - 1 - kk));
            }
            if (kk <= i - l && k - kk <= r - (i + 1)) {
                ans = std::max(  // +
                    ans, solve(l, i, kk) + solve(i + 1, r, k - kk));
            }
        }
    }
    // cout << l << '\t' << r << '\t' << k << "\tans "<<ans<<endl;
    results[l][r][k] = ans;
    return ans;
}

int main() {
    int m;
    int n, k;
    cin >> m;
    while (m--) {
        for (int i = 0; i < 25; ++i) {  // init results[][][]
            for (int j = 0; j < 25; ++j) {
                for (int k = 0; k < 25; ++k) {
                    results[i][j][k] = -1;
                }
            }
        }
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        cout << solve(0, n - 1, k) << endl;
    }
    return 0;
}