#include <iostream>
#include <map>
#include <string>

using namespace std;
std::map<int, int> m;
int n, x;
int arr[50005];
int main() {
    int M;
    cin >> M;
    while (M--) {
        cin >> n >> x;
        int i = 0;
        for (i = 0; i < n; ++i) {
            cin >> arr[i];
            if (m[arr[i]])
                m[arr[i]]++;
            else
                m.insert(std::pair<int, int>(arr[i], 1));
        }
        for (i = 0; i < n; ++i) {
            auto iter = m.find(x - arr[i]);
            if (iter != m.end()) {
                cout << "yes" << endl;
                break;
            }
        }
        if (i == n) cout << "no" << endl;
        m.clear();
    }
    return 0;
}