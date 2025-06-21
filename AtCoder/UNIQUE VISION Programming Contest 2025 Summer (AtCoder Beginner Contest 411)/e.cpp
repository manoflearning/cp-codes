#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<vector<int>> a(n, vector<int>(6));
    for (auto &i : a) for (auto &j : i) cin >> j;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            pq.push({a[i][j], i});
        }
    }

    ll ans = 0;

    ll cnt = 1, cnt_prv = 0;
    vector<ll> cases(n);
    int num_0 = n;
    while (!pq.empty()) {
        auto [x, idx] = pq.top();
        pq.pop();

        if (cases[idx] > 0) {
            cnt = cnt * power(cases[idx], MOD - 2) % MOD;
        } else {
            num_0--;
        }
        cases[idx]++;
        cnt = cnt * cases[idx] % MOD;

        if (!pq.empty() && pq.top().fr == x) continue;

        if (num_0 == 0) {
            ans = (ans + (cnt - cnt_prv) * x % MOD) % MOD;
            ans = (ans + MOD) % MOD;
            cnt_prv = cnt;
        }
    }

    assert(cnt == power(6, n));

    cout << ans * power(power(6, n), MOD - 2) % MOD;
}
