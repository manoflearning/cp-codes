#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        ll ans = 0;

        // case 1: if a[i] == a[j]
        map<pii, int> acc;
        for (int i = 0; i < n; i++) {
            if (1 <= (ll)a[i] * a[i] - b[i] && (ll)a[i] * a[i] - b[i] <= n)
                ans += acc[{a[i], (ll)a[i] * a[i] - b[i]}];
            acc[{a[i], b[i]}]++;
        }
        acc.clear();

        // case 2: if a[i] != a[j]
        const int sq = sqrt(2 * n) + 10;

        vector<vi> sum(sq + 1, vi(n + 1));

        vi ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return a[i] < a[j];
        });

        for (const int i : ord) {
            for (ll aj = 1; aj <= min(a[i] - 1, sq); aj++) {
                if (1 <= aj * a[i] - b[i] && aj * a[i] - b[i] <= n)
                    ans += sum[aj][aj * a[i] - b[i]];
            }

            if (a[i] <= sq) sum[a[i]][b[i]]++;
        }

        cout << ans << '\n';
    }
}
