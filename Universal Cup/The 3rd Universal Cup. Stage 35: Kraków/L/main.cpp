#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int n, q;
struct Point {
    ll x, y;
};
Point p[5050];

bool ccw(const Point &a, const Point &b, const Point &c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return res > 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> p[i].x >> p[i].y;
        }

        while (q--) {
            int a, b, c;
            cin >> a >> b >> c;

            bool ans = 1;
            for (int i = 1; i <= n; i++) {
                if (i == a || i == b || i == c) continue;
                bool x1 = ccw(p[a], p[b], p[i]);
                bool x2 = ccw(p[b], p[c], p[i]);
                bool x3 = ccw(p[c], p[a], p[i]);
                if (x1 == x2 && x2 == x3) { ans = 0; break; }
            }

            cout << (ans ? "YES" : "NO") << '\n';
        }
    }
}
