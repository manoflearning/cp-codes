#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll a, b, c, d, m;
        cin >> a >> b >> c >> d >> m;

        unordered_map<ll, int> dist;
        
        queue<pll> qu;
        qu.push({a, b});
        dist[(a << 30) + b] = 0;

        while (!qu.empty()) {
            auto [x, y] = qu.front();
            qu.pop();

            // cout << x << ' ' << y << '\n';
            if (pll{x, y} == pll{c, d}) break;
            if (dist[(x << 30) + y] >= 25) break;

            ll nx = -1, ny = -1;
            {
                nx = (x & y), ny = y;
                if (!dist.count((nx << 30) + ny)) {
                    dist[(nx << 30) + ny] = dist[(x << 30) + y] + 1;
                    qu.push({nx, ny});
                }
            }
            {
                nx = (x | y), ny = y;
                if (!dist.count((nx << 30) + ny)) {
                    dist[(nx << 30) + ny] = dist[(x << 30) + y] + 1;
                    qu.push({nx, ny});
                }
            }
            {
                nx = x, ny = (x ^ y);
                if (!dist.count((nx << 30) + ny)) {
                    dist[(nx << 30) + ny] = dist[(x << 30) + y] + 1;
                    qu.push({nx, ny});
                }
            }
            {
                nx = x, ny = (y ^ m);
                if (!dist.count((nx << 30) + ny)) {
                    dist[(nx << 30) + ny] = dist[(x << 30) + y] + 1;
                    qu.push({nx, ny});
                }
            }
        }

        // cout << sz(dist) << '\n';
        cout << (dist.count((c << 30) + d) ? dist[(c << 30) + d] : -1) << '\n';
    }
}
