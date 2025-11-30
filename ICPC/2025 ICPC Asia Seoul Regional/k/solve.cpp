#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 2020;

struct point {
    ll x, y;
    bool operator<(const point &rhs) const {
        return x ^ rhs.x ? x < rhs.x : y < rhs.y;
    }
};

point o;

int n;
vector<point> p, pp;
ll ans[N];

ll ccw(const point &a, const point &b, const point &c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return res > 0 ? 1 : -1;// (res < 0 ? -1 : 0);
}
// ll dist(const point &v) {
//     return (v.x - o.x) * (v.x - o.x) + (v.y - o.y) * (v.y - o.y);
// }

int get_quadrants(point v, int j, int k) {
    v.x -= o.x, v.y -= o.y;
    if (k == 1) {
        int tmp = v.x;
        v.x = -v.y;
        v.y = tmp;
    } else if (k == 2) {
        v.x = -v.x;
        v.y = -v.y;
    }
    v.x += o.x, v.y += o.y;

    point v90 = v;
    v90.x -= o.x, v90.y -= o.y;
    {
        int tmp = v90.x;
        v90.x = -v90.y;
        v90.y = tmp;
    }
    v90.x += o.x, v90.y += o.y;

    j %= sz(pp);
    return ccw(o, v, pp[j]) > 0 && ccw(o, v90, pp[j]) <= 0;
}

int get_wtf(int i, int j) {
    int ret = j - i;
    ret = (ret % sz(pp) + sz(pp)) % sz(pp); 
    return ret;
}

void foreach_o() {
    sort(all(pp), [&](const point &lhs, const point &rhs) {
        if ((lhs < o) ^ (rhs < o)) return (lhs < o) < (rhs < o);
        return ccw(o, lhs, rhs) > 0;
        // if (ccw(o, lhs, rhs)) return ccw(o, lhs, rhs) > 0;
        // return dist(lhs) < dist(rhs);
    });

    // cout << "o = {" << o.x << ", " << o.y << "}\n";
    // cout << "pp = {";
    // for (auto &i : pp) {
    //     cout << "{" << i.x << ", " << i.y << "},"; 
    // }
    // cout << "}\n\n";

    int i90 = 0, i180 = 0, i270 = 0;
    for (int i = 0; i < sz(pp); i++) {
        point v = pp[i];
        while (i90 < i || (i90 - i < sz(pp) && get_quadrants(v, i90 + 1, 0))) i90++;
        while (i180 < i90 || (i180 - i90 < sz(pp) && get_quadrants(v, i180 + 1, 1))) i180++;
        while (i270 < i180 || (i270 - i180 < sz(pp) && get_quadrants(v, i270 + 1, 2))) i270++;

        // cout << i << ' ' << i90 << ' ' << i180 << ' ' << i270 << endl;
        int ab = get_wtf(i, i90);
        int c = get_wtf(i90, i180);
        // cout << ab << ' ' << c << endl;
        ans[ab] += 1;
        ans[ab + c] -= 1;
        
        int fuck = get_wtf(i270, i) - 1;
        int shit = get_wtf(i180, i270);
        // cout << fuck << ' ' << shit << '\n';
        if (fuck >= 0) {
            ans[fuck] += 1;
            ans[fuck + shit] -= 1;
        }
    }

    // for (int i = 0; i <= n - 3; i++) {
    //     cout << ans[i] << ' ';
    // }
    // cout << "\n\n";
}

void solve() {
    for (int i = 0; i < n; i++) {
        o = p[i];
        pp.clear();
        for (int j = 0; j < n; j++) {
            if (i != j) pp.push_back(p[j]);
        }

        foreach_o();
    }

    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n;
    p.resize(n);
    for (auto &[y, x] : p) cin >> y >> x;

    solve();

    for (int i = 0; i <= n - 3; i++)
        cout << ans[i] << '\n';
}