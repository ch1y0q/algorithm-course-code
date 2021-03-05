#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int M, N;
int *arr;

void lds() {  // longest decreasing(non-increasing) subsequence
    int *f = new int[N];
    for (int i = 0; i < N; i++) {
        f[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] <= arr[j]) {
                f[i] = std::max(f[i], f[j] + 1);
            }
        }
    }
    int maxx = 0;
    for (int i = 0; i < N; i++) {
        maxx = std::max(maxx, f[i]);
    }
    cout << maxx << endl;
    return;
}

int main() {
    cin >> M;
    while (M--) {
        cin >> N;
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        lds();
    }
    return 0;
}