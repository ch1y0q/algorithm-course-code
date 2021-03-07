#include <algorithm>
#include <iostream>
using namespace std;
int s[505], v[505], f[105];
int N, C;
void bag() {
    for (int i = 1; i <= N; i++) {
        for (int j = C; j >= s[i]; j--) {
            f[j] = std::max(f[j], f[j - s[i]] + v[i]);
        }
    }
    cout << (f[C] < 0 ? 0 : f[C]) << endl;
}

int main() {
    int M;
    cin >> M;
    while (M--) {
        f[0] = 0;
        for (int i = 1; i < 105; ++i) f[i] = -1e7;  // initialize
        cin >> N >> C;
        for (int i = 1; i <= N; i++) {
            cin >> s[i] >> v[i];
        }
        bag();
    }
    return 0;
}