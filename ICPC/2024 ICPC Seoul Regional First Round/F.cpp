#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point { double x, y; };

int n;
vector<Point> a;
Point p1, p2;

ll ccw(const Point &a, const Point& b, const Point &c) {
    double res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        double deg1, deg2;
        cin >> deg1 >> deg2;
        double x1 = cos(deg1 / 1800 * M_PI) * 1000;
        double y1 = sin(deg1 / 1800 * M_PI) * 1000;
        double x2 = cos(deg2 / 1800 * M_PI) * 1000;
        double y2 = sin(deg2 / 1800 * M_PI) * 1000;
        a.push_back({ x1, y1 });
        a.push_back({ x2, y2 });
    }
    {
        double deg, r;
        cin >> deg >> r;
        double x = cos(deg / 1800 * M_PI) * r;
        double y = sin(deg / 1800 * M_PI) * r;
        p1 = {x, y};
    }
    {
        double deg, r;
        cin >> deg >> r;
        double x = cos(deg / 1800 * M_PI) * r;
        double y = sin(deg / 1800 * M_PI) * r;
        p2 = {x, y};
    }

    int ans = 0;
    for (int i = 0; i < 2 * n; i += 2) {
        if (ccw(a[i], a[i + 1], p1) != ccw(a[i], a[i + 1], p2)) ans++;
    }

    cout << (ans & 1 ? "NO" : "YES");
}
