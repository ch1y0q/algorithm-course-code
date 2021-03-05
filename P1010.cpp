#include <iostream>
#include <string>
using namespace std;
int *a;

void find(int *a, int low, int high, int x, int father)
{
    // [low, high]
    if (high < low)
    {
        cout << "not found, father is " << father << endl;
        return;
    }
    int mid = (low + high) / 2;
    if (father == -1)
        father = a[mid];
    if (a[mid] == x)
    {
        cout << "success, father is " << father << endl;
        return;
    }
    if (a[mid] > x)
    {
        find(a, low, mid - 1, x, a[mid]);
    }
    else
    {
        find(a, mid + 1, high, x, a[mid]);
    }
}

int main()
{
    int M;
    cin >> M;
    while (M--)
    {
        int N, x;
        cin >> N >> x;
        a = new int[N];
        for (int i = 0; i < N; i++)
        {
            cin >> a[i];
        }
        find(a, 0, N - 1, x, -1);
    }
    return 0;
}