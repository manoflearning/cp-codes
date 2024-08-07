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

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n, k, x;
        cin >> n >> k >> x;

        vector<int> a(n);
        for (auto& i : a) cin >> i;

        sort(all(a));

        vector<int> psum(n + 1);
        for (int i = 0; i < n; i++)
            psum[i + 1] = a[i] + psum[i];
        
        int ans = -INF;
        for (int r = n - k; r <= n; r++) {
            int l = max(1, r - x + 1);
            ans = max(ans, -(psum[r] - psum[l - 1]) + psum[l - 1]);
        }

        cout << ans << '\n';

        // int ans = -INF;
        // for (int i = n - x; i >= max(0, n - x - k); i--) {
        //     ans = max(ans, psum[i] - (psum[i + x] - psum[i]));
        // }

        // cout << ans << '\n';
    }
}