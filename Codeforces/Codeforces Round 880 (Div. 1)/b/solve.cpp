#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

constexpr ll INF = 1e18;

ll n, m, k;
vector<ll> a, psum;
vector<ll> cc;
ll ans1 = -1, ans2 = INF;

void input() {
    cin >> n >> m >> k;
    a.resize(n);
    for (auto &i : a) cin >> i;
}

void coor_comp() {
    cc.push_back(-1);
    cc.push_back(0);
    for (auto &i : a) {
        if (0 <= i - 2) cc.push_back(i - 2);
        if (0 <= i - 1) cc.push_back(i - 1);
        cc.push_back(i);
        if (i + 1 <= m) cc.push_back(i + 1);
        if (i + 2 <= m) cc.push_back(i + 2);
    }
    cc.push_back(m);

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (auto &i : a) {
        i = lower_bound(all(cc), i) - cc.begin();
    }
}

ll sum(ll l, ll r) { return psum[r] - psum[l - 1]; }

void solve() {
    int l = 1, r = 1;

    for (int i = 1; i < sz(cc); i++) {
        while (l < i && l + 1 < sz(cc) && k < sum(l, i)) l++;
        if (1 < l && sum(l, i) < k) l--;
        while (l < i && sum(l + 1, i) >= k) l++;
        while (r < i || (r + 1 < sz(cc) && sum(i, r) < k)) r++;

        ll x = cc[i], a = cc[l], b = cc[r];

        const ll lb = sum(l, i) >= k ? (a + x) / 2 + 1 : 0;
        const ll ub = sum(i, r) >= k ? (b + x + 1) / 2 - 1 : m;

        ll res = max(0ll, ub - lb + 1);
        if (ans1 < res) {
            ans1 = res, ans2 = x;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    coor_comp();

    psum.assign(sz(cc), 0);
    for (auto &i : a) psum[i]++;
    
    for (int i = 1; i < sz(cc); i++)
        psum[i] += psum[i - 1];

    solve();

    cout << ans1 << ' ' << ans2 << '\n';
}
