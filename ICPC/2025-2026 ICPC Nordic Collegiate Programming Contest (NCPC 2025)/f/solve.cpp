#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Tree {
    int flag;
    vector<int> t, lazy;
    Tree(int n, const vector<int> &a) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, 0);
        lazy.assign(flag << 1, 0);

        for (int i = flag; i < flag + n; i++) t[i] = a[i - flag];
        for (int i = flag - 1; i >= 1; i--) 
            t[i] = max(t[i << 1], t[i << 1 | 1]);
    }
    void prop(int v) {
        if (!lazy[v]) return;
        if (v < flag) {
            lazy[v << 1] += lazy[v];
            lazy[v << 1 | 1] += lazy[v];
        }
        t[v] += lazy[v];
        lazy[v] = 0;
    }
    void update(int l, int r, int val, int v, int vl, int vr) {
        prop(v);
        if (vr < l || r < vl) return;
        if (l <= vl && vr <= r) {
            lazy[v] += val;
            prop(v);
            return;
        }
        const int mid = (vl + vr) >> 1;
        update(l, r, val, v << 1, vl, mid);
        update(l, r, val, v << 1 | 1, mid + 1, vr);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }
    int query(int l, int r, int v, int vl, int vr) {
        prop(v);
        if (vr < l || r < vl) return 0;
        if (l <= vl && vr <= r) return t[v];
        const int mid = (vl + vr) >> 1;
        return max(query(l, r, v << 1, vl, mid), query(l, r, v << 1 | 1, mid + 1, vr));
    }
    int lower_bound(int val, int v, int vl, int vr) {
        prop(v);
        if (vl == vr) return vl;

        prop(v << 1);
        prop(v << 1 | 1);
        
        const int mid = (vl + vr) >> 1;
        if (val <= t[v << 1]) return lower_bound(val, v << 1, vl, mid);
        else return lower_bound(val, v << 1 | 1, mid + 1, vr);
    }
    void update(int l, int r, int val) { update(l, r, val, 1, 1, flag); }
    int query(int l, int r) { return query(l, r, 1, 1, flag); }
    int lower_bound(int val) { return lower_bound(val, 1, 1, flag); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<int> a(n), b(n);
    for (auto &i : a) {
        cin >> i;
        i++;
    }
    for (auto &i : b) {
        cin >> i;
        i++;
    }

    vector<int> orda(n), ordb(n), locb(n);
    iota(all(orda), 0);
    sort(all(orda), [&](int i, int j) { return a[i] > a[j]; });
    iota(all(ordb), 0);
    sort(all(ordb), [&](int i, int j) { return b[i] < b[j]; });

    for (int i = 0; i < n; i++) locb[ordb[i]] = i + 1;

    vector<int> c = b;
    sort(all(c));

    vector<pii> ans;

    Tree seg(n, c);

    // DEBUG
    // for (int x = 1; x <= n; x++) {
    //     cout << seg.query(x, x) << ' ';
    // }
    // cout << '\n';

    for (int i : orda) {
        const int val = seg.query(n - a[i] + 1, n - a[i] + 1);
        if (val == 0) {
            cout << "impossible\n";
            exit(0);
        }

        int l = seg.lower_bound(val);
        int r = min(n + 1, seg.lower_bound(val + 1));
        const int cnt1 = n - r + 1;
        const int cnt2 = a[i] - cnt1;

        bool pad = 0;
        if (locb[i] < l || l + cnt2 - 1 < i && i < r) {
            pad = 1;
            seg.update(locb[i], locb[i], -1);
        }

        seg.update(l, l + cnt2 - 1 - pad, -1);
        seg.update(r, n, -1);
        for (int x = l; x <= l + cnt2 - 1 - pad; x++) {
            if (i != ordb[x - 1]) ans.push_back({i, ordb[x - 1]});
        }
        for (int x = r; x <= n; x++) {
            if (i != ordb[x - 1]) ans.push_back({i, ordb[x - 1]});
        }

        // DEBUG
        // for (int x = 1; x <= n; x++) {
        //     cout << seg.query(x, x) << ' ';
        // }
        // cout << '\n';
    }

    sort(all(ans));

    cout << n << ' ' << sz(ans) << '\n';
    for (auto &i : ans) {
        cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }
}
