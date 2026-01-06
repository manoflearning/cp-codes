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

constexpr int P = 101010;

// what: 2D segment tree with coordinate compression for sparse updates/queries.
// time: prep O(q log q), update/query O(log^2 n); memory: O(q log q)
// constraint: x is 1-indexed [1..n]; y is coordinate value; call mark_set/mark_query first, then prep, then set/query.
// usage: seg2d_comp st(n); st.mark_set(x, y); st.mark_query(x1, x2, y1, y2); st.prep(); st.set(x, y, v); st.query(x1, x2, y1, y2);
struct seg2d_comp { // x: 1-indexed
    int n;
    vector<vector<ll>> a;
    vector<vector<int>> used;
    // unordered_map<ll, ll> mp;
    seg2d_comp(int n) : n(n), a(2 * n), used(2 * n) {}
    void mark_set(int x, int y) {
        // goal: record y-coordinates that will be updated.
        for (x += n - 1; x >= 1; x >>= 1) used[x].push_back(y);
    }
    void mark_query(int x1, int x2, int y1, int y2) {
        // goal: record y-coordinates needed for queries.
        for (x1 += n - 1, x2 += n; x1 < x2; x1 >>= 1, x2 >>= 1) {
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
            a[i].assign(sz(used[i]) << 1, 0);
        }
    }
    void set(int x, int y) {
        // goal: set a[x][y] = v using compressed tree.
        ll k = (ll)x << 32 | (unsigned)y;
        // ll d = v - mp[k];
        // mp[k] = v;
        for (x += n - 1; x >= 1; x >>= 1) {
            int i = lower_bound(all(used[x]), y) - used[x].begin() + sz(used[x]);
            for (a[x][i]++; i > 1; i >>= 1)
                a[x][i >> 1] = a[x][i] + a[x][i ^ 1];
        }
    }
    ll qry1d(int x, int y1, int y2) const {
        // result: sum on row segment [y1, y2].
        ll ret = 0;
        y1 = lower_bound(all(used[x]), y1) - used[x].begin();
        y2 = lower_bound(all(used[x]), y2) - used[x].begin();
        for (y1 += sz(used[x]), y2 += sz(used[x]) + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) ret += a[x][y1++];
            if (y2 & 1) ret += a[x][--y2];
        }
        return ret;
    }
    ll query(int x1, int x2, int y1, int y2) const {
        // result: sum on rectangle [x1..x2] x [y1..y2].
        ll ret = 0;
        for (x1 += n - 1, x2 += n; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ret += qry1d(x1++, y1, y2);
            if (x2 & 1) ret += qry1d(--x2, y1, y2);
        }
        return ret;
    }
};

struct event {
    char op; int x, y;
};

int n;
vector<event> a;
vector<vector<int>> t;
vector<int> dep, in, out;
int idx;

void dfs(int v) {
    in[v] = ++idx;
    for (auto &i : t[v]) {
        dep[i] = dep[v] + 1;
        dfs(i);
    }
    out[v] = idx;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    a.resize(n);

    t.resize(P);
    for (auto &i : a) {
        cin >> i.op >> i.x >> i.y;
        if (i.op == 'Z') t[i.y].push_back(i.x);
    }

    dep.resize(P);
    in.resize(P), out.resize(P);
    dep[1] = 1;
    dfs(1);

    seg2d_comp seg(P);
    for (auto &i : a) {
        if (i.op == 'Z') {
            seg.mark_set(in[i.x], dep[i.x]);
        } else {
            int y = dep[i.x] + i.y + 1;
            seg.mark_query(in[i.x], out[i.x], y, y);
        }
    }
    seg.prep();

    for (auto &i : a) {
        if (i.op == 'Z') {
            seg.set(in[i.x], dep[i.x]);
        } else {
            int y = dep[i.x] + i.y + 1;
            cout << seg.query(in[i.x], out[i.x], y, y) << '\n';
        }
    }
}
