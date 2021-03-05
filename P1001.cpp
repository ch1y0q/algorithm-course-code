#include <iostream>
#include <string>
using namespace std;
int main()
{
    string str;
    getline(cin, str);
    int t = stoi(str), count = 0;
    while (t--)
    {
        getline(cin, str);
        count = 0;
        for (char c : str)
        {
            if (c >= '0' && c <= '9')
            {
                count++;
            }
        }
        cout << count << endl;
    }
    return 0;
}