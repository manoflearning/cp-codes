#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct PST {
    struct Node { ll l, r, val; };
    vector<Node> t;

    void addNode() {
        t.push_back({ -1, -1, 0 });
    }
    void build(ll l, ll r, ll n)  {
        if (l == r) return;
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        ll mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
    }
    void modify(ll p, ll val, ll l, ll r, ll n1, ll n2) {
        if (p < l || r < p) {
            t[n2].l = t[n1].l;
            t[n2].r = t[n1].r;
            t[n2].val = t[n1].val;
            return;
        }

        t[n2].val = t[n1].val + val;
        if (l == r) return;
        ll mid = (l + r) >> 1;
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
    }
    ll query(ll l, ll r, ll n, ll nl, ll nr) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].val;
        int mid = (nl + nr) >> 1;
        return query(l, r, t[n].l, nl, mid) + query(l, r, t[n].r, mid + 1, r);
    }
}pst;

int n, m;
ll a[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    cin >> m;
    for (int i = 0; i < m; i++) {
        int op, x, y, z;
        cin >> op >> x >> y;
        if (op == 2) cin >> z;
        
    }
}