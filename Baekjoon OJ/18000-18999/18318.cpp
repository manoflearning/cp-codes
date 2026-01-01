#pragma GCC optimize("O3")
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

constexpr ll INF = 1e18;

// what: 2D segment tree with coordinate compression for sparse updates/queries.
// time: prep O(q log q), update/query O(log^2 n); memory: O(q log q)
// constraint: call mark_set/mark_qry first, then prep, then set/query.
// usage: seg2d_comp st(n); st.mark_set(x, y); st.mark_qry(x1, x2, y1, y2); st.prep(); st.set(x, y, v); st.query(x1, x2, y1, y2);
struct seg2d_comp { // 0-indexed
    int n;
    vector<vector<ll>> a;
    vector<vector<int>> used;
    // unordered_map<ll, ll> mp;
    seg2d_comp(int n) : n(n), a(2 * n), used(2 * n) {}
    void mark_set(int x, int y) {
        // goal: record y-coordinates that will be updated.
        for (x += n; x >= 1; x >>= 1) used[x].push_back(y);
    }
    void mark_qry(int x1, int x2, int y1, int y2) {
        // goal: record y-coordinates needed for queries.
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) {
                used[x1].push_back(y1);
                used[x1++].push_back(y2);
            }
            if (x2 & 1) {
                used[--x2].push_back(y1);
                used[x2].push_back(y2);
            }
        }
    }
    void prep() {
        // goal: compress and allocate internal trees.
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i].empty()) {
                sort(all(used[i]));
                used[i].erase(unique(all(used[i])), used[i].end());
            }
            used[i].shrink_to_fit();
            a[i].assign(sz(used[i]) << 1, INF);
        }
    }
    void set(int x, int y, ll v) {
        // goal: set a[x][y] = v using compressed tree.
        // ll k = (ll)x << 32 | (unsigned)y;
        // if (!mp.count(k)) mp[k] = INF;
        // ll d = v - mp[k];
        // mp[k] = v;
        for (x += n; x >= 1; x >>= 1) {
            int i = lower_bound(all(used[x]), y) - used[x].begin() + sz(used[x]);
            for (a[x][i] = min(a[x][i], v); i > 1; i >>= 1)
                a[x][i >> 1] = min(a[x][i], a[x][i ^ 1]);
        }
    }
    ll qry1d(int x, int y1, int y2) const {
        // result: sum on row segment [y1, y2].
        ll ret = INF;
        y1 = lower_bound(all(used[x]), y1) - used[x].begin();
        y2 = lower_bound(all(used[x]), y2) - used[x].begin();
        for (y1 += sz(used[x]), y2 += sz(used[x]) + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) ret = min(ret, a[x][y1++]);
            if (y2 & 1) ret = min(ret, a[x][--y2]);
        }
        return ret;
    }
    ll query(int x1, int x2, int y1, int y2) const {
        // result: sum on rectangle [x1..x2] x [y1..y2].
        ll ret = INF;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ret = min(ret, qry1d(x1++, y1, y2));
            if (x2 & 1) ret = min(ret, qry1d(--x2, y1, y2));
        }
        return ret;
    }
};

int n, p;
vector<pair<pii, pii>> a;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> p;
    for (int i = 0; i < p; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 < 0 || y1 < 0) continue;
        if (n < x2 || n < y2) continue;
        a.push_back({{x1, y1}, {x2, y2}});
    }

    sort(all(a));

    seg2d_comp seg{2 * p + 2};

    vector<ll> cc_x;
    cc_x.push_back(0);
    for (auto &i : a) {
        cc_x.push_back(i.fr.fr);
        cc_x.push_back(i.sc.fr);
    }
    cc_x.push_back(n);

    sort(all(cc_x));
    cc_x.erase(unique(all(cc_x)), cc_x.end());

    for (auto &i : a) {
        i.fr.fr = lower_bound(all(cc_x), i.fr.fr) - cc_x.begin();
        i.sc.fr = lower_bound(all(cc_x), i.sc.fr) - cc_x.begin();
    }

    seg.mark_set(0, 0);
    for (auto &i : a) {
        seg.mark_set(i.sc.fr, i.sc.sc);
        seg.mark_qry(0, i.fr.fr, 0, i.fr.sc);
    }
    seg.mark_qry(0, sz(cc_x) - 1, 0, n);

    seg.prep();

    seg.set(0, 0, 2 * n);

    for (auto &i : a) {
        ll res = 0;
        res += seg.query(0, i.fr.fr, 0, i.fr.sc);
        res -= (n - cc_x[i.fr.fr]) + (n - i.fr.sc);
        seg.set(i.sc.fr, i.sc.sc, res + (n - cc_x[i.sc.fr]) + (n - i.sc.sc));
    }

    cout << seg.query(0, sz(cc_x) - 1, 0, n) << '\n';
}

// 어떤 springboard의 끝점 {x2, y2}에서 오거나
// 원점 {0, 0}에서 오거나

// 세그에는 dp[x][y] + (n - x) + (n - y)를 입력하고, 최솟값 세그