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

ll dp[1010101], psum[1010101];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	dp[0] = 1;
    dp[1] = 2;
	dp[2] = 7;
	psum[0] = 1;
	psum[1] = 3;
	psum[2] = 10;
    for (int i = 3; i < 1010101; i++) {
        dp[i] = 2 * psum[i - 3] + 3 * dp[i - 2] + 2 * dp[i - 1];
        dp[i] %= MOD;

		psum[i] = dp[i] + psum[i - 1];
		psum[i] %= MOD;
    }

    int n; cin >> n;
    cout << dp[n];

	return 0;
}