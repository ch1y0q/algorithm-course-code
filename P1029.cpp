// p3366
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 20005;
int n, m, sum, k;
int fa[maxn];
struct edge {
    int x, y, v;
    bool operator>(const edge &other) const { return v > other.v; }
    bool operator<(const edge &other) const { return v < other.v; }
} edges[maxn];

void addEdge(int x, int y, int v, int num) {
    edges[num].x = x;
    edges[num].y = y;
    edges[num].v = v;
}

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unionn(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) fa[x] = y;
}

void Kruskal() {
    k = sum = 0;
    sort(edges + 1, edges + m + 1);
    for (int i = 1; i <= m; ++i) {
        if (find(edges[i].x) != find(edges[i].y)) {
            unionn(edges[i].x, edges[i].y);
            k++;
            sum += edges[i].v;
        }
        if (k == n - 1) break;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) fa[i] = i;
        for (int i = 1; i <= m; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            addEdge(x, y, z, i);
        }
        Kruskal();
        if (k != n - 1)
            cout << "-1" << endl;
        else
            cout << sum << endl;
    }
    return 0;
}