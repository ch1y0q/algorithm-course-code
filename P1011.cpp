#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n = 0;

struct point_t {
    int x;
    int y;
    bool operator==(const point_t a) { return a.x == x && a.y == y; }
} points[50005], points_y[50005];

double distance(int i, int j) {
    if (i == j) return 1e7;
    return 1.0 * std::sqrt(std::pow(points[i].x - points[j].x, 2) +
                           std::pow(points[j].y - points[i].y, 2));
}

double distance(point_t i, point_t j) {
    if (i == j) return 1e7;
    return 1.0 * std::sqrt(std::pow(i.x - j.x, 2) + std::pow(j.y - i.y, 2));
}

bool cmp_x(point_t p1, point_t p2) { return p1.x < p2.x; }

bool cmp_y(point_t p1, point_t p2) { return p1.y < p2.y; }

double merge(int l, int r) {  // [l,r]
    // cout << "l: " << l << " r: " << r << endl;
    if (l >= r) {
        // cout << 1e7 << endl;
        return 1e7;
    }
    if (r - l == 1) {
        // cout << distance(l, r) << endl;
        return distance(l, r);
    }
    int mid = (l + r) / 2;
    double dis = std::min(merge(l, mid), merge(mid + 1, r));
    int mx = points[mid].x, my = points[mid].y;
    std::vector<point_t> middle;
    for (int i = l; i <= r; ++i) {
        if (points[i].x >= mx - dis &&
            points[i].x <= mx + dis) {  // [mx - dis, mx + dis]
            middle.push_back(points[i]);
        }
    }
    std::sort(middle.begin(), middle.end(), cmp_y);
    for (int k = 0; k < middle.size(); ++k) {
        // cout<<point.x<<" "<<point.y<<endl;
        // cout<<"dis"<<dis<<endl;
        point_t point = middle[k];
        int j = 0, i = 0;
        while (j < middle.size()) {
            if (middle[j].y >= point.y) break;
            ++j;
        }
        for (; i < 7; ++i) {
            if (i + j >= middle.size()) break;
            dis = std::min(dis, distance(point, middle[i + j]));
        }
    }
    return dis;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i].x = points_y[i].x = x;
        points[i].y = points_y[i].y = y;
    }
    // preprocess
    std::sort(points, points + n, cmp_x);  // using STL sort
    cout << fixed << setprecision(2) << merge(0, n - 1) << endl;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        solve();
    }
    return 0;
}