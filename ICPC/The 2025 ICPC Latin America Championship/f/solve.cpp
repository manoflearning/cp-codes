#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Sign {
    int a, b, h;
};

struct SegTime {
    int flag;
	vector<vector<int>> t;

    void init(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, vector<int>{});
    }
    void add(int l, int r, int val, int v, int vl, int vr) {
        if (r < vl || vr < l) return;
        if (l <= vl && vr <= r) {
            t[v].push_back(val);
            return;
        }
        const int mid = (vl + vr) >> 1;
        add(l, r, val, v << 1, vl, mid);
        add(l, r, val, v << 1 | 1, mid + 1, vr);
    }
    void add(int l, int r, int val) { add(l, r, val, 1, 1, flag); }
};

struct SegSpace {
    int flag;
    vector<int> t;
    vector<pii> lazy; // {h, id}
    vector<vector<pii>> rb;
    void init(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, 0);
        lazy.assign(flag << 1, {0, -1});
        rb.assign(n, vector<pii>{});
    }
    void prop(int v) {
        // TODO
    }
    void update(int l, int r, pii val, int v, int vl, int vr) {
        // TODO
    }
    void update(int l, int r, pii val) { update(l, r, val, 1, 1, flag); }
    int query(int l, int r, int v, int vl, int vr) {
        // TODO
    }
    int query(int l, int r) { query(l, r, 1, 1, flag); }
    void rollback(int id) {
        // TODO
    }
};

int n;

vector<Sign> arr;
vector<int> st, en;

vector<pii> qu;

vector<int> ans;
SegTime seg_t;
SegSpace seg_s;

void dnc(int v, int vl, int vr) {
    for (const int id : seg_t.t[v]) {
        seg_s.update(arr[id].a, arr[id].b, {arr[id].h, id});
    }

    if (vl == vr) {
        if (vl <= n && qu[vl].first != -1) {
            ans[vl] = seg_s.query(qu[vl].first, qu[vl].second);
        }
    } else {
        const int mid = (vl + vr) >> 1;
        dnc(v << 1, vl, mid);
        dnc(v << 1 | 1, mid + 1, vr);
    }

    for (const int id : seg_t.t[v]) {
        seg_s.rollback(id);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cin >> n;

    st.assign(n, -1), en.assign(n, n);
    qu.assign(n + 1, {-1, -1});
    ans.assign(n + 1, -1);
    for (int t = 1; t <= n; t++) {
        char op; cin >> op;
        if (op == '+') {
            int a, b, h;
            cin >> a >> b >> h;
            arr.push_back({a, b, h});
            st[sz(arr) - 1] = t;
        } else if (op == '-') {
            int id; cin >> id;
            id--;
            en[id] = t - 1;
        } else if (op == '?') {
            int l, r;
            cin >> l >> r;
            qu[t] = {l, r};
        }
    }

    vector<int> cc(1, -1);
    for (auto &i : arr) {
        cc.push_back(i.a);
        cc.push_back(i.b);
    }
    for (auto &i : qu) {
        cc.push_back(i.first - 1);
        cc.push_back(i.first);
        cc.push_back(i.second);
        cc.push_back(i.second + 1);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (auto &i : arr) {
        i.a = lower_bound(all(cc), i.a) - cc.begin();
        i.b = lower_bound(all(cc), i.b) - cc.begin();
    }
    for (auto &i : qu) {
        i.first = lower_bound(all(cc), i.first) - cc.begin();
        i.second = lower_bound(all(cc), i.second) - cc.begin();
    }

    seg_t.init(n);
    for (int i = 0; i < sz(arr); i++) {
        seg_t.add(st[i], en[i], i);
    }

    seg_s.init(sz(cc));

    dnc(1, 1, seg_t.flag);

    for (int t = 1; t <= n; t++) {
        if (ans[t] != -1) cout << ans[t] << '\n';
    }
}
