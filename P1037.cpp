#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;
int n, m, k;

vector<int> like[105];
int matching[105]; /* �洢����� */
int check[105];

// This is a bipartite graph matching problem
// solve with DFS-based Hungarian algorithm
bool dfs(int u) {
    for (auto i = like[u].begin(); i != like[u].end(); ++i) {
        int v = *i;
        if (!check[v]) {      // ���ڽ���·��
            check[v] = true;  // ���뽻��·
            if (matching[v] == -1 || dfs(matching[v])) {
                // �����δ�ǵ㣬˵������·Ϊ����·���򽻻�·���������سɹ�
                matching[v] = u;
                matching[u] = v;
                return true;
            }
        }
    }
    return false;  // ����������·������ʧ��
}

int hungarian() {
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    rep(u, 0, n - 1) {
        if (matching[u] == -1) {
            memset(check, 0, sizeof(check));
            if (dfs(u)) ++ans;
        }
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        rep(i, 0, n - 1) like[i].clear();
        rep(i, 0, n - 1) {
            cin >> k;
            rep(j, 1, k) {
                int t;
                cin >> t;
                like[i].push_back(t + n - 1);
                like[t + n - 1].push_back(i);
            }
        }
        cout << hungarian() << endl;
    }
    return 0;
}