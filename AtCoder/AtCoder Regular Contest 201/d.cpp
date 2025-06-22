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
        int n, m;
        cin >> n >> m;

        vector<int> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        ll l = 0, r = m - 1;
        while (l < r) {
            ll mid = (l + r) >> 1;

            set<int> st;
            map<ll, ll> ra;
            for (int i = 0; i < n; i++) {
                st.insert(a[i]);
                ra[a[i]]++;
            }

            bool is_valid = 1;

            map<ll, ll> lb, ub;
            for (int i = 0; i < n; i++) {
                if (b[i] <= mid) {
                    lb[0]++;
                    ub[mid - b[i]]++;
                    st.insert(0);
                    st.insert(mid - b[i]);
                } else {
                    lb[m - b[i]]++;
                    ub[m + mid - b[i]]++;
                    st.insert(m - b[i]);
                    st.insert(m + mid - b[i]);
                }
            }

            ll acc_op = 0, acc_cl = 0;
            for (auto x : st) {
                acc_op += lb[x];
                
                ll done = min(acc_op, ra[x]);
                acc_op -= done;
                acc_cl += done;

                if (acc_cl < ub[x]) {
                    is_valid = 0;
                    break;
                } else acc_cl -= ub[x];
            }

            if (is_valid) r = mid;
            else l = mid + 1;
        }

        cout << l << '\n';
    }
}
