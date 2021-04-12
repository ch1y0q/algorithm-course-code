#include <cstdio>
#include <ctime>
#include <iostream>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)
#define MAXN 100005
#define INF 1000007

#define random(a, b) \
    ((a) + rand() % ((b) - (a) + 1))  // random(a,b)生成[a,b]的随机整数
int main() {
    srand(time(NULL));
    int T = random(1, 15);
    printf("%d\n", T);
    while (T--) {
        int n = random(1, MAXN);
        printf("%d\n", n);
        rep(i, 1, n) { printf("%d ", random(1, 100)); }
        printf("\n");
        rep(i, 1, n) { printf("%d ", random(1, 100)); }
        printf("\n");
    }
    return 0;
}