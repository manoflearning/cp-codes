#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

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
        vector<ll> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        ll mxa = 0;
        for (auto &i : a) mxa = max(mxa, i);

        ll mxa_diff = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == mxa) {
                mxa_diff = max(mxa_diff, b[i] - a[i]);
            }
        }

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int p1, int p2) {
            if (a[p1] ^ a[p2]) return a[p1] > a[p2];
            else return b[p1] > b[p2];
        });

        ll ans = mxa_diff;

        ll prv = mxa_diff;
        for (auto i : ord) {
            if (b[i] < a[i]) ans = INF;
            if (b[i] - a[i] > prv) ans = INF;
            prv = min(prv, b[i] - a[i]);
        }

        cout << (ans == INF ? -1 : ans) << '\n';
    }
}
