#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;
const int MOD = 998'244'353;

struct DSU {
    vector<int> uf;
    void build(int n) {
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;
        uf[u] = v;
    }
} dsu;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int n, a[N];
vector<int> ra[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]].push_back(i);
    }

    int c = 0;

    bool all_even = 1;
    for (int i = 1; i < N; i++) {
        all_even &= (sz(ra[i]) % 2 == 0);
        if (!ra[i].empty()) c++;
    }

    int d = (all_even ? c : 0);
    if (all_even) {
        vector<pii> arr;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j + 1 < sz(ra[i]); j += 2) {
                arr.push_back({ra[i][j], ra[i][j + 1]});
            }
        }

        sort(all(arr));

        dsu.build(N);

        stack<int> stk;
        for (auto [l, r] : arr) {
            if (!stk.empty() && r < stk.top()) {
                d = 0;
                break;
            }

            if (!stk.empty() && l < stk.top()) {
                if (dsu.find(a[stk.top()]) != dsu.find(a[l])) {
                    dsu.merge(a[stk.top()], a[l]);
                    d--;
                }
            }
            stk.push(r);
        }
    }

    // DEBUG
    // cout << c << ' ' << d << '\n';

    ll ans = (power(2, c) - (d > 0 ? power(2, d) : 0) + MOD) % MOD * power(2, MOD - 2) % MOD;
    cout << ans;
}
