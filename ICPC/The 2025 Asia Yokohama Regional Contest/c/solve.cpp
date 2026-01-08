#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;

int n;
vector<ll> b;
map<ll, vector<pll>> mp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    b.assign(n, 0);
    for (auto &i : b) cin >> i;

    ll ans1 = 0;

    ll n_cycles = INF, mn = INF;
    for (auto &i : b) mn = min(mn, i);
    n_cycles = mn;

    vector<ll> psum(202020);
    for (int i = 0; i < n; i++) {
        if (b[(i + 1) % n] > b[i]) {
            psum[b[i] + 1]++;
            psum[b[(i + 1) % n] + 1]--;
        }
    }
    for (int i = 1; i < 202020; i++) {
        psum[i] += psum[i - 1];
        ans1 += psum[i];
        if (psum[i] > 0)
            n_cycles = max(0ll, n_cycles - psum[i] + 1);
    }
    ans1 += n_cycles;

    cout << ans1 << '\n';
    if (200'000 < ans1) exit(0);

    n_cycles = mn;

    vector<pll> stk;
    for (int i = 0; i < 2 * n; i++) {
        while (!stk.empty()) {
            auto [h, j] = stk.back();
            if (h <= b[i % n]) break;
            mp[h].push_back({j, i - 1});
            // cout << h << ' ' << j << ' ' << i - 1 << '\n';
            stk.pop_back();
        }

        if (i < n) {
            for (int h = b[i] + 1; h <= b[(i + 1) % n]; h++) {
                stk.push_back({h, i + 1});
            }
        }
    }

    vector<pll> ans2;
    for (int d = mn + 1; d <= 200'000; d++) {
        vector<pll> arr = mp[d];
        assert(psum[d] == sz(arr));
        sort(all(arr));
        ll dup_cnt = max<ll>(0ll, min<ll>(sz(arr) - 1, n_cycles));
        n_cycles -= dup_cnt;

        int l = 0, r = dup_cnt;
        for (int l = 0, r = dup_cnt; l < sz(arr); l++, r = (r + 1) % sz(arr)) {
            ans2.push_back({arr[l].fr, arr[r].sc});
        }
    }
    while (n_cycles--) {
        ans2.push_back({0, n - 1});
    }

    assert(sz(ans2) == ans1);
    for (auto &[l, r] : ans2) {
        cout << l % n + 1 << ' ' << r % n + 1 << '\n';
    }
}
