#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;
const int MAXN = 50505;

struct Point {
    ll x, y;
};

int n;
Point a[MAXN];

ll one_enclosure() {
    ll mn_x = INF, mx_x = -INF;
    ll mn_y = INF, mx_y = -INF;
    for (int i = 1; i <= n; i++) {
        mn_x = min(mn_x, a[i].x);
        mx_x = max(mx_x, a[i].x);
        mn_y = min(mn_y, a[i].y);
        mx_y = max(mx_y, a[i].y);
    }
    return (mx_x - mn_x) * (mx_y - mn_y);
}

ll two_enclosures_sort_by_x() {
    sort(a + 1, a + n + 1, [&](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });

    vector<ll> prefix_max_y(n + 2, -INF), prefix_min_y(n + 2, INF);
    vector<ll> suffix_max_y(n + 2, -INF), suffix_min_y(n + 2, INF);

    for (int i = 1; i <= n; i++) {
        prefix_max_y[i] = max(a[i].y, prefix_max_y[i - 1]);
        prefix_min_y[i] = min(a[i].y, prefix_min_y[i - 1]);
    }
    for (int i = n; i >= 1; i--) {
        suffix_max_y[i] = max(a[i].y, suffix_max_y[i + 1]);
        suffix_min_y[i] = min(a[i].y, suffix_min_y[i + 1]);
    }

    ll ret = INF;

    for (int i = 1; i + 1 <= n; i++) {
        if (a[i].x == a[i + 1].x) continue;
        ll area_l = abs((a[i].x - a[1].x) * (prefix_max_y[i] - prefix_min_y[i]));
        ll area_r = abs((a[n].x - a[i + 1].x) * (suffix_max_y[i + 1] - suffix_min_y[i + 1]));
        ret = min(ret, area_l + area_r);
    }

    return ret;
}

ll two_enclosures() {
    ll ret = INF;

    ret = min(ret, two_enclosures_sort_by_x());
    for (int i = 1; i <= n; i++) swap(a[i].x, a[i].y);
    ret = min(ret, two_enclosures_sort_by_x());

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    cout << one_enclosure() - two_enclosures();
}