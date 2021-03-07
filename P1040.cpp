#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int **arr;

bool find(int m, int n, int target) {
    int r = 0, c = n - 1;
    while (r < m) {
        while (target < arr[r][c] && c > 0) c--;
        if (target == arr[r][c])
            return true;
        else
            c++, r++;
    }
    return false;
}

int main() {
    int nums, m, n, target;
    cin >> nums;
    while (nums--) {
        cin >> m >> n >> target;
        arr = new int *[m];
        for (int i = 0; i < m; i++) {
            arr[i] = new int[n];
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }
        cout << boolalpha << find(m, n, target) << endl;
    }
    return 0;
}