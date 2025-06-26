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
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) {
            cin >> i;
            i *= 2;
        }

        set<ll> st;
        for (auto i : a) {
            st.insert(i - 1);
            st.insert(i);
            st.insert(i + 1);
        }

        sort(all(a));

        vector<ll> psum(n);
        psum[0] = a[0];
        for (int i = 1; i < n; i++) {
            psum[i] = a[i] + psum[i - 1];
        }

        ll ans = 0;

        int idx = 0;
        for (auto t : st) {
            while (idx < n && a[idx] <= t) {
                idx++;
            }

            if (idx == n) break;

            int l = idx - 1, r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;

                ll res_n = psum[mid];
                ll res_d = mid + 1;

                if (res_n < a[idx] * res_d) l = mid;
                else r = mid - 1;
            }
            // cout << idx << ' ' << l << '\n';
            ans = max<ll>(ans, l - idx + 1);
        }

        cout << ans << '\n';
    }
}
