#include <iostream>
#include <string>
using namespace std;

int *b;
int *a;
int n;
void quicksort(int l, int r, int depth)
{
    // [l, r]
    if (l >= r)
    {
        return;
    }
    if (r - l <= 1) // 区间较小，直接用冒泡排序
    {
        for (int i = l; i < r; ++i)
        {
            for (int j = r; j > i; --j)
            {
                if (a[j] > a[j - 1])
                {
                    int t = a[j];
                    a[j] = a[j - 1];
                    a[j - 1] = t;
                }
            }
        }
    }
    int p = l;
    for (int i = l; i <= r; i++)
    {
        if (a[l] > a[i])
        {
            p++;
            int temp = a[p];
            a[p] = a[i];
            a[i] = temp;
        }
    }
    int temp = a[l];
    a[l] = a[p];
    a[p] = temp;

    if (depth == 1)
    {
        b[p] = a[p];
    }
    if (depth == 2)
    {
        for (int i = l; i <= r; i++)
        {
            b[i] = a[i];
        }
    }

    quicksort(l, p - 1, depth + 1);
    quicksort(p + 1, r, depth + 1);
}

int solve()
{
    cin >> n;
    a = new int[n];
    b = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    quicksort(0, n - 1, 1);

    for (int i = 0; i < n; i++)
    {
        cout << b[i] << ' ';
    }
    cout << endl;
    return 0;
}

int main()
{
    int m;
    cin >> m;
    while (m--)
    {
        solve();
    }
    return 0;
}