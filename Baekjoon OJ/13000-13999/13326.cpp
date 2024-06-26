#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Point { ll x, y; };

int n;
vector<Point> p;

void input() {
    cin >> n;
    p.resize(n);
    for (auto& i : p) cin >> i.x >> i.y;
}

double ans = 1e18;

ll dist(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void solve() {
    if (n == 2) { ans = 0; return; }

    int s = 0, e = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist(p[s], p[e]) < dist(p[i], p[j])) s = i, e = j;
        }
    }

    vector<int> ord;
    for (int i = 0; i < n; i++) {
        if (i != s && i != e) ord.push_back(i);
    }
    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return dist(p[s], p[p1]) < dist(p[s], p[p2]);
    });

    vector<ll> pmax(sz(ord)), smax(sz(ord));

    pmax[0] = dist(p[s], p[ord[0]]);
    for (int i = 1; i < sz(ord); i++) {
        pmax[i] = pmax[i - 1];
        pmax[i] = max(dist(p[s], p[ord[i]]), pmax[i]);
        for (int j = 0; j < i; j++) {
            pmax[i] = max(dist(p[ord[j]], p[ord[i]]), pmax[i]);
        }
    }

    smax[sz(ord) - 1] = dist(p[e], p[ord[sz(ord) - 1]]);
    for (int i = sz(ord) - 2; i >= 0; i--) {
        smax[i] = smax[i + 1];
        smax[i] = max(dist(p[e], p[ord[i]]), smax[i]);
        for (int j = sz(ord) - 1; j > i; j--) {
            smax[i] = max(dist(p[ord[j]], p[ord[i]]), smax[i]);
        }
    }

    ans = min(ans, sqrt(smax[0]));
    ans = min(ans, sqrt(pmax[sz(ord) - 1]));
    for (int i = 0; i + 1 < sz(ord); i++) {
        ans = min(ans, sqrt(pmax[i]) + sqrt(smax[i + 1]));
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << fixed;
    cout.precision(5);
    cout << ans;
}