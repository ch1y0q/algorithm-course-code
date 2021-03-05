#include <iostream>
#include <string>
using namespace std;

int *b = nullptr, n;

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
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int l = 0, r = n, mid = (l + r - 1) / 2;
    int mid1 = (l + mid) / 2, mid2 = (mid + r) / 2;

    mergesort(a, l, mid1 + 1);
    mergesort(a, mid1 + 1, mid + 1);
    mergesort(a, mid + 1, mid2 + 1);
    mergesort(a, mid2 + 1, r);

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
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