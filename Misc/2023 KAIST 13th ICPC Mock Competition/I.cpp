#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;

int n;
vector<ll> a(MAXN);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];

        ll opt = -1, opt_val = -1;
        for (int d = 0; d <= 30; d++) {
            ll bit = (1ll << d) - 1;

            vector<int> ord(n);
            iota(all(ord), 1);

            sort(all(ord), [&](int p1, int p2) {
                return (a[p1] & bit) < (a[p2] & bit);
            });

            int prv = -1;
            for (int i = 0; i < n; i++) {
                if ((a[ord[i]] & bit) == prv + 1) prv++;
                else if ((a[ord[i]] & bit) <= prv) continue;
                else if ((a[ord[i]] & bit) > prv + 1) break;
            }
            ll res = prv + 1;

            if (opt_val < res) {
                opt = bit;
                opt_val = res;
            }
        }

        cout << opt << '\n';
    }
}
