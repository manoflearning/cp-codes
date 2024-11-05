#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const __int128_t INF = 1e27;

int n;
ll m, d, x;
ll s[2020], e[2020];
__int128_t cost[2020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> d >> x;

    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> e[i];
    }

    for (int i = 1; i <= n; i++) {
        if (i == 1) cost[i] = s[i] - 1;
        
        if (i == n) {
            cost[i + 1] = m - e[i];
        }
        
        if (i > 1) cost[i] = s[i] - e[i - 1] - (d + 1);
        assert(cost[i] >= 0);
        assert(cost[i + 1] >= 0);
    }

    __int128_t ans = INF;
    for (int i = 1; i <= n + 1; i++) {
        __int128_t len = min<__int128_t>(x + d, cost[i]), score = 0;

        for (int j = 1; 1 <= i - j || i + j <= n + 1; j++) {
            if (len == x + d) break;

            __int128_t csum = 0;
            if (1 <= i - j) csum += cost[i - j];
            if (i + j <= n + 1) csum += cost[i + j];

            __int128_t rem = min(x + d - len, csum);
            len += rem;
            score += j * rem;
        }

        if (len == x + d)
            ans = min(ans, score);
    }

    if (ans == INF) cout << -1;
    else {
        if (ans >= (ll)1e18) {
            string s1 = to_string((ll)(ans / (ll)1e18));
            string s2 = to_string((ll)(ans % (ll)1e18));
            while (sz(s2) < 18) s2 = "0" + s2;
            cout << s1 << s2;
        } else {
            cout << (ll)ans;
        }
    }
}
