#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int M, N;
int *arr;

void how_many() {
    int k = 0, i, j;
    int **systems = new int *[N + 5];

    for (i = 0; i < N; i++) {
        bool flag = true;
        for (j = 1; j <= k; j++) {
            if (systems[j][systems[j][0]] >= arr[i]) {
                systems[j][++systems[j][0]] = arr[i];
                flag = false;
                break;
            }
        }
        if (flag) {
            // need more systems
            k++;
            systems[k] = new int[N + 5];
            for (int i = 0; i < N + 5; i++) {
                systems[k][i] = 0;
            }
            systems[k][0]++;
            systems[k][1] = arr[i];
        }
    }
    cout << k << endl;
}

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
    cout << maxx << ' ';
    delete[] f;
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
        how_many();
        delete[] arr;
    }
    return 0;
}