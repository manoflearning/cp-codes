#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        // vector<ll> b(n);
        // iota(all(b), 1);

        // ll ans = 0;
        // for (auto &i : a) {
        //     ans += i * (i + 1) / 2;
        // }

        // int lb = 0, ub = n - 1;
        // while (lb < ub) {       
        //     ll l = 0, r = 5e3;
        //     while (l < r) {
        //         ll mid = (l + r + 1) >> 1;

        //         __int128_t res = 0;
        //         res += (__int128_t)(a[lb] + (a[lb] + mid / b[lb] - 1)) * mid / b[lb];
        //         res += (__int128_t)(a[lb] + mid / b[lb]) * (mid % b[lb]);
        //         res -= (__int128_t)(a[ub] + (a[ub] - mid / b[ub] + 1)) * mid / b[ub];
        //         res -= (__int128_t)(a[ub] - mid / b[ub]) * (mid % b[ub]);
        //         res += (__int128_t)k * mid;

        //         ll nxt_lb = a[lb] + mid / b[lb] + (mid % b[lb] ? 0 : -1);
        //         ll nxt_ub = a[ub] - mid / b[ub] + (mid % b[ub] ? 0 : +1);

        //         if (res <= 0 && nxt_lb <= a[lb + 1] && a[ub - 1] <= nxt_ub) l = mid;
        //         else r = mid - 1;
        //     }

        //     if (l == 0) break;

        //     ll op_cnt = l;

        //     ans += (a[lb] + (a[lb] + op_cnt / b[lb] - 1)) * op_cnt / b[lb];
        //     ans += (a[lb] + op_cnt / b[lb]) * (op_cnt % b[lb]);
        //     ans -= (a[ub] + (a[ub] - op_cnt / b[ub] + 1)) * op_cnt / b[ub];
        //     ans -= (a[ub] - op_cnt / b[ub]) * (op_cnt % b[ub]);
        //     ans += k * op_cnt;

        //     ll nxt_lb = a[lb] + op_cnt / b[lb] + (op_cnt % b[lb] ? 0 : -1);
        //     ll nxt_ub = a[ub] - op_cnt / b[ub] + (op_cnt % b[ub] ? 0 : +1);

        //     if (nxt_lb == a[lb + 1]) {
        //         if (op_cnt % b[lb]) {
        //             a[lb] = nxt_lb - 1;
        //             b[lb + 1] += op_cnt % b[lb];
        //             b[lb] -= op_cnt % b[lb];
        //         } else {
        //             b[lb + 1] += b[lb];
        //             lb++;
        //         }
        //     } else {
        //         a[lb] = nxt_lb;
        //     }

        //     if (nxt_ub == a[ub - 1]) {
        //         if (op_cnt % b[ub]) {
        //             a[ub] = nxt_ub + 1;
        //             b[ub - 1] += op_cnt % b[ub];
        //             b[ub] -= op_cnt % b[ub];
        //         } else {
        //             b[ub - 1] += b[ub];
        //             ub--;
        //         }
        //     } else {
        //         a[ub] = nxt_ub;
        //     }
        // }
        
        // cout << ans << '\n';

        ll ans = 0;
        for (auto &i : a) {
            ans += i * (i + 1) / 2;
        }

        priority_queue<ll, vector<ll>, greater<ll>> pq_mn, pq_mn_2, pq_mn_3;
        priority_queue<ll> pq_mx, pq_mx_2, pq_mx_3;
        for (auto &i : a) {
            pq_mn.push(i);
            pq_mx.push(i);
        }

        while (1) {
            ll mn = pq_mn.top(); pq_mn.pop();
            ll mx = pq_mx.top(); pq_mx.pop();

            ll diff = mx - mn - 1;

            if (diff <= k) break;

            ll op_cnt = (diff - k) / 2 + 1;

            ans -= (mx + (mx - op_cnt + 1)) * op_cnt / 2;
            ans += (mn + 1 + mn + op_cnt) * op_cnt / 2;
            ans += k * op_cnt;
            // cout << mn << ' ' << mx << ' ' << op_cnt << '\n';
            mn += op_cnt;
            mx -= op_cnt;

            pq_mn_2.push(mn);
            pq_mx_2.push(mn);
            pq_mn_3.push(mx);
            pq_mx_3.push(mx);
        }

        k = 0;
        while (!pq_mn_2.empty()) {
            ll mn = pq_mn_2.top(); pq_mn_2.pop();
            ll mx = pq_mx_2.top(); pq_mx_2.pop();

            ll diff = mx - mn - 1;

            if (diff <= k) break;

            ll op_cnt = (diff - k) / 2 + 1;

            ans -= (mx + (mx - op_cnt + 1)) * op_cnt / 2;
            ans += (mn + 1 + mn + op_cnt) * op_cnt / 2;
            ans += k * op_cnt;
        }
        while (!pq_mn_3.empty()) {
            ll mn = pq_mn_3.top(); pq_mn_3.pop();
            ll mx = pq_mx_3.top(); pq_mx_3.pop();

            ll diff = mx - mn - 1;

            if (diff <= k) break;

            ll op_cnt = (diff - k) / 2 + 1;

            ans -= (mx + (mx - op_cnt + 1)) * op_cnt / 2;
            ans += (mn + 1 + mn + op_cnt) * op_cnt / 2;
            ans += k * op_cnt;
        }

        cout << ans << '\n';
    }
}
