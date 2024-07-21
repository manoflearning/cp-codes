#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

int n, m, k;
ll c[1 << 19], d[1 << 19], x[1 << 19];
map<pll, int> mp;
vector<int> idxs[1 << 19];
ll ans[1 << 19];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        cin >> c[i] >> d[i] >> x[i];
        // if (mp.count({ c[i], d[i] })) {
        //     x[mp[{ c[i], d[i] }]] = x[mp[{ c[i], d[i] }]] * x[i] % m;
        // }
        // else {
            idxs[d[i]].push_back(i);
            // mp[{ c[i], d[i] }] = i;
        // }
    }

    for (int i = 0; i < (1 << n); i++) {
        ans[i] = 1;
    }

    for (int bit = 0; bit < (1 << n); bit++) { // |bit| = O(2^n) = 25 * 10^4
        int pc = 0;
        for (int b = 0; b < n; b++) {
            if ((1 << b) & bit) pc++;
        }

        for (auto& i : idxs[pc]) {
            int j = bit ^ c[i];
            ans[j] = (ans[j] * x[i]) % m;
        }
    }

    for (int i = 0; i < (1 << n); i++) {
        cout << ans[i] << ' ';
    }
}