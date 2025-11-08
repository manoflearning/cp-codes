#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

struct point { int y, x; };

int n, m;
vector<string> a;
vector<point> p;

void draw(point now, int dy, int dx, vector<string> &b) {
    b[now.y][now.x] = '#';
    if (dy < 0) draw({now.y - 1, now.x}, dy + 1, dx, b);
    else if (dy > 0) draw({now.y + 1, now.x}, dy - 1, dx, b);
    else if (dx < 0) draw({now.y, now.x - 1}, dy, dx + 1, b);
    else if (dx > 0) draw({now.y, now.x + 1}, dy, dx - 1, b);
    else return;
}

pair<int, vector<string>> f(point st) {
    int w = 0;
    vector<string> b = a;
    
    for (int i = 0; i < sz(p); i++) {
        w += abs(p[i].y - st.y) + abs(p[i].x - st.x);

        draw(st, p[i].y - st.y, p[i].x - st.x, b);
    }

    return {w, b};
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (a[y][x] == '#') p.push_back({y, x});
        }
    }

    int opt_val = INF;
    vector<string> opt;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            auto [w, b] = f({y, x});
            if (w < opt_val) {
                opt_val = w;
                opt = b;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << opt[i] << '\n';
    }
}
