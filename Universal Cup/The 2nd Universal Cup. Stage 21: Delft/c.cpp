#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point {
    ll x, y;
    char c;
    bool operator<(const Point& rhs) const {
        return (x ^ rhs.x ? x < rhs.x : y < rhs.y);
    }
    bool operator>(const Point& rhs) const {
        return (x ^ rhs.x ? x > rhs.x : y > rhs.y);
    }
    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    Point operator-(const Point& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }
    ll operator*(const Point& rhs) const { // cross product
        return x * rhs.y - y * rhs.x;
    }
};

ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

int n;
vector<Point> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a)
        cin >> i.x >> i.y >> i.c;

    int ans = 1;

    set<char> st;
    for (auto& i : a) {
        if (st.count(i.c)) ans = 2;
        st.insert(i.c);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (i != j && j != k && i != k) {
                    if (ccw(a[i], a[j], a[k]) > 0 && a[i].c == a[k].c) {
                        cout << "Infinity";
                        return 0;
                    }
                }
            }
        }
    }

    cout << ans;
}
