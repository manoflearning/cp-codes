#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Point {
    double x, y;
};

ll w, g;
int l, u;
vector<Point> a, b;

void init() {}

void input() {
    cin >> w >> l >> u >> g;
    a.resize(l);
    b.resize(u);
    for (auto &i : a) cin >> i.x >> i.y;
    for (auto &i : b) cin >> i.x >> i.y;
}

double get_y(int i, double x, const vector<Point> &arr) {
    double p = (double)(arr[i + 1].y - arr[i].y) / (arr[i + 1].x - arr[i].x);
    return p * (x - arr[i].x) + arr[i].y;
}

int get_idx(double x, const vector<Point> &arr) {
    int s = 0, e = sz(arr) - 2;
    while (s < e) {
        int mid = (s + e + 1) >> 1;
        if (arr[mid].x <= x) s = mid;
        else e = mid - 1;
    }
    return s;
}

double get_area(double sx, double ex, const vector<Point> &arr) {
    double ret = 0;
    for (ll x = 0; x <= w; x++) {
        if (x - 1 < sx && sx < x) {
            int idx1 = get_idx(sx, arr);
            double y1 = get_y(idx1, sx, arr);
            int idx2 = get_idx(x, arr);
            double y2 = get_y(idx2, x, arr);
            ret += (y1 + y2) * (x - sx);
        }
        if (x < ex && ex < x + 1) {
            int idx1 = get_idx(x, arr);
            double y1 = get_y(idx1, x, arr);
            int idx2 = get_idx(ex, arr);
            double y2 = get_y(idx2, ex, arr);
            ret += (y1 + y2) * (ex - x);
        }
        if (x + 1 <= w && sx <= x && x + 1 <= ex) {
            int idx1 = get_idx(x, arr);
            double y1 = get_y(idx1, x, arr);
            int idx2 = get_idx(x + 1, arr);
            double y2 = get_y(idx2, x + 1, arr);
            ret += (y1 + y2);
        }
    }
    return ret;
}

vector<double> solve(double ea) {
    vector<double> ret;
    double sx = 0;
    while (sz(ret) < g - 1) {
        double s = sx, e = w;
        for (int bs = 0; bs < 60; bs++) {
            double mid = (s + e) / 2;
            double area = get_area(sx, mid, b) - get_area(sx, mid, a);
            if (area < ea) s = mid;
            else e = mid;
        }
        ret.push_back(s);
        sx = s;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ":\n";

        init();

        input();

        double ta = get_area(0, w, b) - get_area(0, w, a);
        vector<double> ans = solve(ta / g);
        cout << fixed;
        cout.precision(8);
        for (auto &i : ans) {
            assert(0 <= i && i <= w);
            cout << (double)i << '\n';
        }
    }
}
