#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point { ll x, y; };
struct Line {
    ll i, j, dx, dy; // i < j, dx >= 0

    bool operator<(const Line& rhs) const {
        if (dy * rhs.dx != rhs.dy * dx) return dy * rhs.dx < rhs.dy * dx;
        return tie(i, j) < tie(rhs.i, rhs.j);
    }
    bool operator==(const Line& rhs) const {
        return dy * rhs.dx == rhs.dy * dx;
    }
};

int n, pos[2020];
Point p[2020];

ll triangleArea(const Point& p1, const Point& p2, const Point& p3) {
    return abs((p2.x - p1.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p1.y));
}

void bulldozerTrick() {
    sort(p + 1, p + 1 + n, [&](const Point& lhs, const Point& rhs) {
        return lhs.x ^ rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    });
    for (int i = 1; i <= n; i++) pos[i] = i;

    vector<Line> arr;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            arr.push_back({ i, j, p[j].x - p[i].x, p[j].y - p[i].y });
        }
    }
    sort(arr.begin(), arr.end());

    ll mn = 1e18, mx = -1e18;
    for (int i = 0, j = 0; i < arr.size(); i = j) {
        while (j < arr.size() && arr[i] == arr[j]) j++; // all line in [i, j) is same
        for (int k = i; k < j; k++) {
            int u = arr[k].i, v = arr[k].j;
            swap(p[pos[u]], p[pos[v]]);
            swap(pos[u], pos[v]);
            if (pos[u] > pos[v]) swap(u, v);
            if (pos[u] > 1) {
                mn = min(mn, triangleArea(p[pos[u]], p[pos[v]], p[pos[u] - 1]));
                mx = max(mx, triangleArea(p[pos[u]], p[pos[v]], p[1]));
            }
            if (pos[v] < n) {
                mn = min(mn, triangleArea(p[pos[u]], p[pos[v]], p[pos[v] + 1]));
                mx = max(mx, triangleArea(p[pos[u]], p[pos[v]], p[n]));
            }
        }
    }

    cout << mn / 2 << (mn & 1 ? ".5" : ".0") << ' ';
    cout << mx / 2 << (mx & 1 ? ".5" : ".0") << '\n';
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        // input
        cin >> n;
        if (!n) break;
        for (int i = 1; i <= n; i++)
            cin >> p[i].x >> p[i].y;

        // solve
        bulldozerTrick();
    }
}