#include <iostream>
#include <string>
using namespace std;

int n, k;
string str;

int solve(int l, int r, int k) {  // [l, r]
    if (!k) {                     // k = 0, return
        return std::stoi(str.substr(l, r - l + 1));
    }
    int ans = -1;
    for (int i = l; i < r; ++i) {
        ans = std::max(
            ans, std::stoi(str.substr(l, i - l + 1)) * solve(i + 1, r, k - 1));
    }
    return ans;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n >> k;
        cin >> str;
        cout << solve(0, n - 1, k) << endl;
    }
    return 0;
}