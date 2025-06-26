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
        int h, w;
        cin >> h >> w;

        string s; cin >> s;

        ll ans = 1;

        vector<int> pd(h + w - 2);
        vector<int> pr(h + w - 2);
        vector<int> pq(h + w - 2);

        for (int i = 0; i < h + w - 2; i++) {
            if (s[i] == 'D') pd[i]++;
            if (s[i] == 'R') pr[i]++;
            if (s[i] == '?') pq[i]++;

            if (i > 0) {
                pd[i] += pd[i - 1];
                pr[i] += pr[i - 1];
                pq[i] += pq[i - 1];
            }
        }

        for (int i = 0; i < h + w - 2; i++) {
            int lb_d = max(0, pq[i] - ((w - 1) - pr[h + w - 3]));
            int ub_d = min(pq[i], (h - 1) - pd[h + w - 3]);

            // cout << lb_d << ' ' << ub_d << '\n';
            ans += ub_d - lb_d + 1;
        }

        cout << ans << '\n';
    }
}
