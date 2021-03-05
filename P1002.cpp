#include <iostream>
#define MAX 1005
using namespace std;
int main()
{
    int m, n, a, min1, min2;
    cin>>m;
    while(m--){
        min1=min2=MAX;
        cin>>n;
        while(n--){
            cin>>a;
            if(a<min1){
                min2=min1;
                min1=a;
            }
            else if (a<min2){
                min2=a;
            }
        }
        cout<<min2<<endl;
    }
    return 0;
}