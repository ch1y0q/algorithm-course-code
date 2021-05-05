/*
dp[root][black]=
        sum(dp[child][white])

dp[root][white]=
        sum(max(dp[child][white], dp[child][black]))

dp[leaf][white]=0
dp[leaf][black]=1
*/

/*Why WA: 比如1 3 ， 2 3 这样的边 1被当做root 然后2就成了孤儿*/

#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

#define MAXN 50005

typedef long long ll;
using namespace std;

int t[MAXN][2];

struct node {
    int parent = 0;
    vector<int> children;
};

node* tree[MAXN];

int n;
int root;

int solve(int r, int color) {
    if (t[r][color] != -1) return t[r][color];
    if (tree[r]->children.size() == 0)  // leaf
    {
        return t[r][color] = color;
    }
    if (color) {
        int sum = 1;
        for (int child : tree[r]->children) {
            sum += solve(child, 0);
        }
        return t[r][color] = sum;
    } else {
        int sumw = 0, sumb = 0;
        for (int child : tree[r]->children) {
            sumw += solve(child, 0);
            sumb += solve(child, 1);
        }
        return t[r][color] = max(sumw, sumb);
    }
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        rep(i, 0, n) {
            tree[i] = new node;
            t[i][0] = t[i][1] = -1;
        }
        rep(i, 1, n - 1) {
            int u, v;
            cin >> u >> v;
            tree[u]->children.push_back(v);
            tree[v]->parent = u;
        }
        rep(i, 1, n)  // find root
        {
            if (tree[i]->parent == 0) {
                root = i;
                break;
            }
        }
        assert(root);
        int ans = max(solve(root, 1), solve(root, 0));
        cout << ans << endl;
        rep(i, 0, n) delete tree[i];
    }
    return 0;
}