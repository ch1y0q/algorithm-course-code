#include <iostream>
#include <string>
using namespace std;
int n, m;
string s, t;
int fail[100005];

void f() {
    int i, j;
    i = 0, j = fail[0] = -1;
    while (i < m) {
        while (j != -1 && t[i] != t[j]) j = fail[j];
        fail[++i] = ++j;
    }
    // for (int i = 0; i < m; ++i) { cout << fail[i] << " "; }
    // cout << endl;
}

int kmp() {
    int ans = 0, i = 0, j = 0;
    while (i < n) {
        if (j == -1) {
            i++, j++;
        } else if (s[i] == t[j]) {
            i++, j++;
        } else {
            j = fail[j];
        }
        if (j == m) {
            ans++;
            j = fail[j];
        }
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        cin >> s >> t;
        f();
        cout << kmp() << endl;
    }
    return 0;
}