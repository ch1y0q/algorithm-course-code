#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> seq;
int a[305][305] = {0};
// a[i][0]: in-degree of node i
void solve(int n)
{
    while (seq.size() < n)
    {
        int i = 1;
        for (; i <= n; ++i)
        {
            if (!a[i][0] && find(seq.begin(), seq.end(), i) == seq.end())
            {
                for (int j = 1; j <= n; ++j)
                {
                    if (a[i][j])
                    {
                        a[j][0]--;
                    }
                }
                seq.push_back(i);
                break;
            }
        }
        if (i == n + 1 && seq.size() < n)
        { //fail to toposort
            cout << 0 << endl;
            return;
        }
    }
    for (int o : seq)
    {
        cout << o << ' ';
    }

    cout << endl;
}

int main()
{
    int t, n, m;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        seq.clear();
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                a[i][j] = 0; // init adjacent matrix
            }
        }
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            a[x][y] = true;
            a[y][0]++;
        }
        solve(n);
    }
    return 0;
}