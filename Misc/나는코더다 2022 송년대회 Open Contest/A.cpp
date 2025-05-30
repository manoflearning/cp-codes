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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll n, k, x;
ll a[88], dp[202 * 88][88];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int du; cin >> du;
    }

    ll ans = 0;

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = x * k; j >= 0; j--) {
            for (int p = k - 1; p >= 0; p--) {
                if (!dp[j][p]) continue;

                dp[j + a[i]][p + 1] = dp[j][p];

                if (p == k - 1) {
                    //cout << j + a[i] << '\n';
                    ll x1 = j + a[i];
                    ll x2 = x * k - x1;
                    ans = max(ans, x1 * x2);
                }
            }
        }
    }

    cout << ans;

	return 0;
}