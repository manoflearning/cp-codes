#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct DSU {
    vector<int> a;
    void init(int n) {
        a.assign(n, -1);
    }
    int find(int x) {
        if (a[x] < 0) return x;
        return a[x] = find(a[x]);
    }
    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        a[v] += a[u];
        a[u] = v;
    }
};

struct point {
    ll x, y;
    int idx;
    bool operator<(const point &rhs) const {
        return pair<ll, ll>{x, y} < pair<ll, ll>{rhs.x, rhs.y};
    }
};

int n;
ll c;
vector<point> a;
DSU dsu; 

void concat() {
    set<tuple<ll, ll, ll>> st;
    for (int i = 0; i < sz(a); i++) {
        const auto [x, y, idx] = a[i];

        vector<tuple<ll, ll, ll>> dels;

        auto it_l = st.lower_bound({y - c, LLONG_MIN, LLONG_MIN});
        auto it_r = st.lower_bound({y + 1, LLONG_MIN, LLONG_MIN});
        while (it_l != it_r) {
            auto [py, px, pidx] = *it_l;
            it_l++;

            if (x - c <= px) {
                dsu.join(idx, pidx);
            }
            dels.push_back({py, px, pidx});
        }

        for (auto &x : dels) st.erase(x);

        st.insert({y, x, idx});
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n >> c;
    a.assign(n, {0, 0, 0});
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a[i].x = x - y; a[i].y = x + y;
        a[i].idx = i;
    }

    sort(all(a));

    dsu.init(n);

    concat();

    for (auto &i : a) i.y = -i.y;
    sort(all(a));
    concat();

    for (auto &i : a) i.y = -i.y, swap(i.x, i.y);
    sort(all(a));
    concat();

    for (auto &i : a) i.y = -i.y;
    sort(all(a));
    concat();
    
    set<int> ans1;
    int ans2 = 0;
    for (int i = 0; i < n; i++) {
        int p = dsu.find(i);
        ans1.insert(p);
        ans2 = max(ans2, -dsu.a[p]);
    }

    cout << sz(ans1) - 1  << ' ' << ans2 << '\n';
}
