#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll MOD = 998'244'353;

// struct fenwick {
//     int n;
//     vector<ll> t;
//     fenwick(int n) : n(n) {
//         t.assign(n + 1, 0);
//     }
//     void add(int i, ll v = 1) {
//         for(; i <= n; i += i & -i) t[i] += v;
//     }
//     ll query(int i) {
//         ll ret = 0;
//         for(; i; i -= i & -i) ret += t[i];
//         return ret;
//     }
// };

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n]) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n] += (nr - nl + 1) * lazy[n];
            lazy[n] = 0;
        }
    }
    void add(int l, int r, ll v, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += v;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, v, n << 1, nl, mid);
        add(l, r, v, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    // fenwick fw(n + 1);

    seg.build(n);
    
    vector<ll> a(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];

        ll t = seg.query(1, a[i]);
        ans += t * (t - 1) / 2;
        
        seg.add(1, a[i], 1);
    }
    cout << ans << '\n';

    // ll ans = 0;
    // for(int i = 1; i <= n; i++) {
        

    //     // if(a[i] <= 1) continue;
    //     // ans += t * t;
    //     // ans += t;
    // }
    // cout << ans << '\n';
}
