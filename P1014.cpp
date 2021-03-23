#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int arr[50005], n;

int solve() {
    int t = arr[0];
    int ans = -1e7;
    for (int i = 1; i < n; ++i) {
        if (t >= 0) {
            t += arr[i];
        } else {
            t = arr[i];
        }
        ans = std::max(ans, t);
    }
    return ans;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        cout << solve() << endl;
    }
    return 0;
}