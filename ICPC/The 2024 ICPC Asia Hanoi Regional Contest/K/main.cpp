#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1010101;

int n, a[N];

int b[N], c[N], cps[N];
// unordered_map<int, int> mp;

// void naive(int x, ll &ans) {
//     ll res = 0;
//     for (int i = 1; i <= n; i++) {
//         if (a[i] < x) res += 2;
//         else if (a[i] == x) res += 1;
//         else if (a[i] > x) res += (a[i] + x - 1) / x + (a[i] % x ? 1 : 0);
//     }
//     ans = min(ans, res);
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        // mp.clear();

        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        sort(a + 1, a + n + 1);

        {
            int j = 0;
            for (int i = 1; i <= n; i++) {
                if (a[i - 1] == a[i]) c[j]++;
                else {
                    j++;
                    b[j] = a[i]; c[j] = 1;
                }
            }
            n = j;
        }
        

        for (int i = 1; i <= n; i++) {
            cps[i] = c[i] + cps[i - 1];
        }

        ll ans = 1e18;

        // for (int cnt = 0; i <= n && cnt <= 10; i++) {
        //     if (a[i - 1] == a[i]) continue;
        //     naive(a[i], ans);
        //     cnt++;
        // }

        for (int i = 1; i <= n; i++) {
            ll res = 2 * cps[i - 1] + c[i];

            int k = i + 1;
            while (k <= n) {
                int l = k, r = n;

                const ll tgt = (b[k] + b[i] - 1) / b[i];
                const int ub = tgt * b[i];

                while (l < r) {
                    const int mid = (l + r + 1) >> 1;

                    if (b[mid] <= ub) l = mid;
                    else r = mid - 1;
                }

                res += (cps[l] - cps[k - 1]) * (tgt + 1) - (b[l] == ub ? c[l] : 0);

                k = l + 1;
            }

            ans = min(ans, res);
        }

        cout << ans << '\n';
    }
}
