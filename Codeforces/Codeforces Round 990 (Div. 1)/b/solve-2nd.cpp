#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        vector<int> smin(n + 1, INF);
        for (int i = n - 1; i >= 0; i--) {
            smin[i] = min(a[i], smin[i + 1]);
        }

        int mmin = INF;
        for (int i = 0; i < n; i++) {
            if (a[i] > smin[i] || a[i] > mmin) {
                a[i]++;
                mmin = min(mmin, a[i]);
            }
        }

        sort(all(a));

        for (auto &i : a) cout << i << ' ';
        cout << '\n';
    }
}