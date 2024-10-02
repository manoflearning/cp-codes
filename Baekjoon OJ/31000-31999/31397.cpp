#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 202020;

struct Point {
    double x, y;
};

int n;
vector<Point> p;
Point u, v;

void input() {
    cin >> n;
    p.resize(n);
    for (auto& i : p) cin >> i.x >> i.y;
}

double dist(const Point& p1, const Point& p2) {

}

double psum[MAXN];
void build_psum() {
    for (int i = 1; i < n; i++) {
        psum[i] = dist(p[i], p[i - 1]) + psum[i - 1];
    }
}

double sum(int l, int r) {
    if (l <= r) return psum[r] - psum[l];
    else return (psum[r] - psum[0]) + (psum[n - 1] - psum[l]) + dist(p[0], p[n - 1]);
}

double area_polygon(const vector<Point>& arr) {

}

Point dividing_point(const Point& p1, const Point& p2, double t) {

}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    build_psum();

    for (int i = 0; i < n; i++) {
        double len1 = sum(0, i);
        double len2 = sum(i, 0);
        double diff = sum(i, (i + 1) % n);

        if (len1 <= len2 && len1 + diff >= len2) {
            double l = 0, r = 1;
            for (int j = 0; j < 60; j++) {
                double mid = (l + r) / 2;
                Point dp = dividing_point(p[i], p[(i + 1) % n], mid);
                if (len1 + dist(p[i], dp) <= len2 + dist(p[(i + 1) % n], dp)) l = mid;
                else r = mid;
            }

            u = p[0], v = dividing_point(p[i], p[(i + 1) % n], l);
            break;
        }
    }


}
