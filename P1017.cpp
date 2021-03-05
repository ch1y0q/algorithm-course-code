#include <iostream>
#include <string>
using namespace std;

int *b = nullptr, n, ans;

void mergesort(int *a, int l, int r)
{ // [l,r)

    if (r - l < 2)
    {
        return;
    }
    int mid = (l + r - 1) / 2;
    mergesort(a, l, mid + 1);
    mergesort(a, mid + 1, r);
    auto pl = l, pb = l, pr = mid + 1;
    while ((pl < mid + 1) && (pr < r))
    {
        while (a[pl] <= a[pr] && (pl < mid + 1))
        {
            b[pb] = a[pl];
            pl++;
            pb++;
        }
        while (a[pl] > a[pr] && (pr < r))
        {
            b[pb] = a[pr];
            pr++;
            pb++;
            ans += mid - pl + 1; // 逆序对计数
        }
    }
    while (pl < mid + 1)
    {
        b[pb] = a[pl];
        pl++;
        pb++;
    }
    while (pr < r)
    {
        b[pb] = a[pr];
        pr++;
        pb++;
    }
    for (int i = l; i < r; ++i)
    {
        a[i] = b[i];
    }
}

void solve(int n)   // 使用mergesort求逆序对数，同P1013
{
    int *a = new int[n];
    b = new int[n];
    ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int l = 0, r = n;

    mergesort(a, l, r);

    for (int i = 0; i < n; i++)
    {
        //cout << a[i] << " ";
    }
    cout << ans << endl;
}

int main()
{
    int m;
    cin >> m;
    while (m--)
    {
        cin >> n;
        solve(n);
    }
    return 0;
}

void solveSlow(int n) // O(n^2)
{
    auto a = new int[n];
    auto b = new int[n];
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        x--;
        a[i] = x;
        b[x] = i;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (a[j] > a[i])
                cnt++;
        }
        /*
        for (int j = 0; j < a[i]; ++j)
        {
            if (b[j] > i)
                cnt++;
        }    */
    }

    cout << cnt << endl;
}
