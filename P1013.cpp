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
            ans += mid - pl + 1; // ÄæÐò¶Ô¼ÆÊý
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

void mergesort(int n)
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
        mergesort(n);
    }
    return 0;
}