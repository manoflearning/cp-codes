#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

inline ll sum(ll l, ll r) {
    return (l + r) * (r - l + 1) / 2;
}

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
        ll m = 0;
        for (auto &i : a) {
            cin >> i;
            m += i;
        }

        ll l = -1e6, r = 1e6;
        while (l < r) {
            ll mid = (l + r) >> 1;

            ll cnt = 0;
            for (auto &i : a) {
                cnt += min(mid, i - k) + k;
                cnt += max(0ll, mid - i);
            }

            if (cnt >= m) r = mid;
            else l = mid + 1;
        }

        ll t = l;

        ll ans = k * m, ans_cnt = 0;
        for (auto &i : a) {
            if (t - 1 >= 1 - k) {
                ans += sum(1 - k, min(t - 1, i - k));
                ans_cnt += min(t - 1, i - k) + k;
            }
            if (t - 1 >= i + 1) {
                ans += sum(i + 1, t - 1);
                ans_cnt += (t - 1) - i;
            }
        }
        ans += (m - ans_cnt) * t;

        cout << ans << '\n';
    }
}
