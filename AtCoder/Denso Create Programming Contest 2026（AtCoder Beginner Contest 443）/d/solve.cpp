#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        ll ans = 0;

        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        for (int i = 0; i < n; i++) {
            pq.push({a[i], i});
        }

        while (!pq.empty()) {
            auto [val, i] = pq.top();
            pq.pop();

            if (a[i] != val) continue;

            for (int d = -1; d <= 1; d += 2) {
                const int j = i + d;
                if (j < 0 || n <= j) continue;
                if (a[j] - 1 <= a[i]) continue;

                ans += a[j] - a[i] - 1;
                a[j] = a[i] + 1;
                pq.push({a[j], j});
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
