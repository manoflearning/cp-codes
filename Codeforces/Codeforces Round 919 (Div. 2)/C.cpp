// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto& i : a) cin >> i;

        int ans = 0;
        for (int k = 1; k <= n; k++) {
            if (n % k) continue;

            bool isValid = true;

            int g = -1;
            for (int i = 0; i < k; i++) {
                for (int j = i; j + k < n; j += k) {
                    if (a[j] - a[j + k] == 0) continue;
                    if (g == -1) g = abs(a[j] - a[j + k]);
                    else g = gcd(g, abs(a[j] - a[j + k]));
                }
                if (g == 1) {
                    isValid = false;
                    break;
                }
            }

            if (g > 1 || g == -1) {
                ans++;
                // cout << k << ' ';
            }
        }
        // cout << '\n';

        cout << ans << '\n';
    }
}