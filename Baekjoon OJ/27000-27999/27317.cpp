#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 101010;

pll a[MAXN];
ll pcost[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m, k, t;
    cin >> n >> m >> k >> t;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i].fr >> a[i].sc;
    }
    a[0].fr = a[0].sc = 0;
    a[n + 1].fr = a[n + 1].sc = m;
    for (int i = 1; i <= n + 1; i++) {
        pcost[i] = (a[i].fr - a[i - 1].sc + t - 1) / t + pcost[i - 1];
    }

    ll ans = 0;

    int p = 0;
    for (int x1 = 0; x1 <= m; x1++) {
        
    }
    
    // int s = 1;
    // for (int e = 1; e <= n; e++) {
    //     while (s + 1 <= e && pcost[e] - pcost[s] > k) s++;
        
    //     ll res = a[e].sc - a[s].fr;
    //     ll cost = pcost[e] - pcost[s];

    //     assert(cost <= k);
        
    //     ll llen = a[s].fr - a[s - 1].sc;
    //     ll rlen = a[e + 1].fr - a[e].sc;
    //     if (cost < k) {
    //         int cnt = min(llen / t, k - cost);

    //         res += cnt * t;
    //         cost += cnt;
    //         llen -= cnt * t;
    //     }
    //     if (cost < k) {
    //         int cnt = min(rlen / t, k - cost);

    //         res += cnt * t;
    //         cost += cnt;
    //         rlen -= cnt * t;
    //     }
    //     if (cost < k && llen < t) {
    //         res += llen;
    //         cost++;
    //     }
    //     if (cost < k && rlen < t) {
    //         res += rlen;
    //         cost++;
    //     }

    //     ans = max(ans, res);
    // }

    // cout << ans;
}
