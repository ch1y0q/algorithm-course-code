// O(m+n) algorithm reference:
// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/comments/36497

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#define INF 1e7

using namespace std;

int n, m, nm;
int arr1[1005], arr2[1005];

int findKth(int l1, int l2, int k) {
    if (l1 > n) return arr2[l2 + k - 1];  // arr1 empty
    if (l2 > m) return arr1[l1 + k - 1];  // arr2 empty
    if (k == 1) {
        return std::min(arr1[l1], arr2[l2]);
    }
    int midVal1 = (l1 + k / 2 - 1 <= n) ? arr1[l1 + k / 2 - 1] : INF;
    int midVal2 = (l2 + k / 2 - 1 <= m) ? arr2[l2 + k / 2 - 1] : INF;
    if (midVal1 < midVal2) {
        return findKth(l1 + k / 2, l2, k - k / 2);
    } else {
        return findKth(l1, l2 + k / 2, k - k / 2);
    }
}

void solve()  // [l,r]
{
    int mid1 = (nm + 1) / 2;
    int mid2 = (nm + 2) / 2;
    cout << (findKth(1, 1, mid1) + findKth(1, 1, mid2)) / 2.0 << endl;
}

int main() {
    int num;
    cin >> num;
    while (num--) {
        cin >> n >> m;
        nm = n + m;
        for (int i = 1; i <= n; i++) {
            cin >> arr1[i];
        }
        for (int i = 1; i <= m; i++) {
            cin >> arr2[i];
        }
        solve();
    }
    return 0;
}