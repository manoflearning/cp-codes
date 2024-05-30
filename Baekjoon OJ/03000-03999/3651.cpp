#include <bits/stdc++.h>
using namespace std;
#define ll long long

__int128_t comb(__int128_t n, __int128_t k) {
    __int128_t ret = 1;
    for (int i = n; i > n - k; i--) ret *= i;
    for (int i = 1; i <= k; i++) ret /= i;
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll m; cin >> m;

    vector<pair<ll, ll>> ans;

    // if k = 1
    ans.push_back({ m, 1 });
    ans.push_back({ m, m - 1 });

    // if k = 2
    ll l = 4, r = 1e8;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (comb(mid, 2) >= m) r = mid;
        else l = mid + 1;
    }
    if (comb(l, 2) == m) {
        ans.push_back({ l, 2 });
        ans.push_back({ l, l - 2 });
    }

    // if k >= 3
    for (ll k = 3; ; k++) {
        if (comb(2 * k, k) > m) break;
        for (ll n = 2 * k; ; n++) {
            __int128_t res = comb(n, k);
            if (res == m) {
                ans.push_back({ n, k });
                ans.push_back({ n, n - k });
            }
            if (res >= m) break;
        }
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    cout << ans.size() << '\n';
    for (auto& i : ans)
        cout << i.first << ' ' << i.second << '\n';
}