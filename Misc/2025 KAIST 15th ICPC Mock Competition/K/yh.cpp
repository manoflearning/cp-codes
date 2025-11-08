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

struct fenwick {
    int n;
    vector<ll> t;
    fenwick(int n) : n(n) {
        t.assign(n + 1, 0);
    }
    void add(int i, ll v = 1) {
        for(; i <= n; i += i & -i) t[i] = (t[i] + v) % MOD;
    }
    ll query(int i) {
        ll ret = 0;
        for(; i; i -= i & -i) ret = (ret + t[i]) % MOD;
        return ret;
    }
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    fenwick fw(n + 15);
    vector<ll> cnt(n + 15);
    
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]++;
        fw.add(a[i]);
        cnt[a[i]]++;
    }

    auto C2 = [&](ll k) -> ll {
        return k * (k - 1) / 2;
    };

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] <= 2) continue;
        ll t = n - fw.query(a[i]);
        ans = (ans + t * (a[i] - 1) * (a[i] - 2) / 2) % MOD;
    }
    for(int i = 1; i <= n + 1; i++) {
        ll t = cnt[i] * (cnt[i] - 1) / 2;
        ll p = ((ll)i - 1) * (i - 2) / 2;
        ans = (ans + (t % MOD) * (p % MOD)) % MOD;
    }

    while(q--) {
        int x, d; cin >> x >> d;
        
        ll p = a[x];
        // if(d > 0) {
        //     ll t = n - fw.query(x - 1);
        //     ans += t * (C2(p + d) - C2(p));
        // } 
        // else {
        //     ll t = n - fw.query(x - 1);
        //     ans += t * (C2(p + d) - C2(p));
        // }
        ll t = (d > 0 ? n - fw.query(p) : n - fw.query(p - 1) - 1);
        ans = (ans + t * (C2(p + d - 1) - C2(p - 1))) % MOD;
        ans = (ans + MOD) % MOD;
        fw.add(p, -1); fw.add(p + d, 1);
        a[x] += d;
        cout << ans << '\n';
    }
}
