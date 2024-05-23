#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;

int flag;
struct Seg {
    vector<ll> t;
    void init(int N) {
        t.clear();
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int N;
ll a[202020];
ll ans = 0;

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
}

void solve() {
    seg.init(N);

    map<int, ll> mp;
    mp[1] = a[1];

    ans = a[1] * a[1] % MOD;

    vector<pair<int, ll>> stk;
    stk.push_back({ 0, 1e18 });
    stk.push_back({ 1, a[1] });

    for (int r = 2; r <= N; r++) {
        for (auto& [l, g] : mp) g = gcd(g, a[r]);
        mp[r] = a[r];

        map<int, ll> tmp;
        set<int> vis;
        for (auto& [l, g] : mp) {
            if (!vis.count(g)) {
                tmp[l] = g;
                vis.insert(g);
            }
        }

        mp = tmp;

        while (stk.back().sc <= a[r]) stk.pop_back();
        stk.push_back({ r, a[r] });

        for (auto& [l, g] : mp) {
            ans = (ans + seg.query(l, r) * g) % MOD;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}