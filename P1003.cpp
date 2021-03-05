#include <iostream>
#include <string>
using namespace std;
int main()
{
    int m, n, *arr;
    cin >> m;
    while (m--)
    {
        cin >> n;
        arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        for (int i = 1; i < n; i++)
        {
            if (arr[i] < arr[i - 1])
            {
                int t = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = t;
            }
        }
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    return 0;
}