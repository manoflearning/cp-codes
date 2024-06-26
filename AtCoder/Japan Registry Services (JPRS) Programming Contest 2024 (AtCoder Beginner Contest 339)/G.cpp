// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

struct PST { // 1-indexed
    int flag; // array size
    struct Node { int l, r; ll val; };
    vector<Node> t;
    vector<int> root;

    void addNode() { t.push_back({ -1, -1, 0 }); }
    void build(int l, int r, int n)  {
        assert(0 <= n && n < sz(t));
        if (l == r) { t[n].val = 0; return; }
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
        t[n].val = t[t[n].l].val + t[t[n].r].val;
    }
    void build(int Flag) {
        addNode();
        root.push_back(sz(t) - 1);
        flag = Flag;
        build(1, flag, root[0]);
    }
    void modify(int p, ll val, int l, int r, int n1, int n2) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));
        if (p < l || r < p) { t[n2] = t[n1]; return; }
        if (l == r) { t[n2].val = val; return; }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[n2].r = t[n1].r;
            addNode();
            t[n2].l = sz(t) - 1;
            modify(p, val, l, mid, t[n1].l, t[n2].l);
        }
        else {
            t[n2].l = t[n1].l;
            addNode();
            t[n2].r = sz(t) - 1;
            modify(p, val, mid + 1, r, t[n1].r, t[n2].r);
        }
        t[n2].val = t[t[n2].l].val + t[t[n2].r].val;
    }
    void modify(int p, ll val) {
        addNode();
        root.push_back(sz(t) - 1);
        modify(p, val, 1, flag, root[sz(root) - 2], root[sz(root) - 1]);
    }
    ll query(int l, int r, int n, int nl, int nr) {
        assert(0 <= n && n < sz(t));
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].val;
        int mid = (nl + nr) >> 1;
        return query(l, r, t[n].l, nl, mid) + query(l, r, t[n].r, mid + 1, nr);
    }
    ll query(int l, int r, int n) {
        assert(n < sz(root));
        return query(l, r, root[n], 1, flag);
    }
}pst;

int N;
ll A[202020];
vector<int> ord;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        ord.push_back(i);
    }

    pst.build(N);

    sort(all(ord), [&](int p1, int p2) {
        return A[p1] < A[p2];
    });

    map<int, int> mp;
    for (int i = 0; i < N; i++) {
        pst.modify(ord[i], A[ord[i]]);
        mp[A[ord[i]]] = i + 1;
    }

    int Q; cin >> Q;
    vector<ll> ans(Q);
    for (int q = 0; q < Q; q++) {
        ll l, r, x;
        cin >> l >> r >> x;
        if (q > 0) {
            l ^= ans[q - 1];
            r ^= ans[q - 1];
            x ^= ans[q - 1];
        }

        auto it = mp.upper_bound(x);
        if (it == mp.begin()) {
            ans[q] = 0;
            continue;
        }
        
        it--;
        ans[q] = pst.query(l, r, it->sc);
    }

    for (int q = 0; q < Q; q++)
        cout << ans[q] << '\n';
}