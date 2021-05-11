#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

#define VT1 v[v.size() - 1]
#define VT2 v[v.size() - 2]
#define MAXN 105
typedef long long ll;
using namespace std;

int n, N;
struct pos_t {
    int x;
    int y;
    double angle;
    double len;
    bool operator<(const pos_t& inPos) {
        return (y < inPos.y || (y == inPos.y && x < inPos.x));
    }
    pos_t(int a = 0, int b = 0) {
        x = a;
        y = b;
    }
} a[MAXN], tmp[MAXN];

vector<pos_t> v;

enum dot_r { LEFT, RIGHT, ONLINE };
dot_r dot(int a, int b, int x, int y) {
    if (a * y - b * x == 0) {
        return ONLINE;
    } else if (a * y - b * x > 0) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

bool canpop(int i) {
    if (v.size() <= 2) {
        return false;
    }
    if (LEFT !=
        dot(VT1.x - VT2.x, VT1.y - VT2.y, a[i].x - VT2.x, a[i].y - VT2.y)) {
        return true;
    }
    return false;
}

bool cmp_angle(pos_t& p1, pos_t& p2) {
    if (p1.angle - p2.angle > 0) {
        return 0;  // >
    } else if (p1.angle - p2.angle < 0) {
        return 1;  // <
    } else {
        if (p1.len - p2.len > 0) {
            return 0;  // >
        } else if (p1.len - p2.len < 0) {
            return 1;  //<
        } else {
            return 0;  //==
        }
    }
}

int main() {
    int m;
    cin >> m;
    rep(T, 1, m) {
        v.clear();

        cout << "case " << T << ":" << endl;

        cin >> N;
        rep(i, 1, N) { cin >> tmp[i].x >> tmp[i].y; }
        sort(tmp + 1, tmp + 1 + N);

        /* remove duplicates */
        n = 0;
        a[++n] = tmp[1];
        rep(i, 2, N) {
            if (tmp[i].x != a[n].x || tmp[i].y != a[n].y) a[++n] = tmp[i];
        }

        /* sort angles */
        rep(i, 2, n) {
            a[i].len = sqrt((a[i].y - a[1].y) * (a[i].y - a[1].y) +
                            (a[i].x - a[1].x) * (a[i].x - a[1].x));
            a[i].angle = acos((a[i].x - a[1].x) / a[i].len);
        }
        sort(a + 2, a + 1 + n, cmp_angle);

        /* start from bottommost-leftmost point */
        v.push_back(a[1]);
        int k = 3;
        for (; k <= n; k++) {
            if (ONLINE != dot(a[k].x - a[1].x, a[k].y - a[1].y, a[2].x - a[1].x,
                              a[2].y - a[1].y)) {
                break;
            }
        }

        v.push_back(a[k - 1]);
        v.push_back(a[k]);
        rep(i, k + 1, n) {
            while (canpop(i)) {
                v.pop_back();
            }
            v.push_back(a[i]);
        }

        /* output answer */
        for (auto& p : v) {
            cout << p.x << " " << p.y << endl;
        }
    }
    return 0;
}
