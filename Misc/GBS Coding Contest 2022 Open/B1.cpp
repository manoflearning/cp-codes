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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
ll h[50505], psum[50505], dp[50505];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        psum[i] = 2 * h[i] + psum[i - 1];
    }

    for (int i = 1; i <= n; i++) dp[i] = INF;
    
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = i - 1; j >= 1; j--) {
            ll len = (psum[i] - psum[j - 1]) - (h[i] + h[j]);
            
            if (len * len >= dp[i]) break;

            ll res = len * len + (h[i] - h[j]) * (h[i] - h[j]);
            dp[i] = min(dp[i], res + dp[j]);
        }
    }

    cout << dp[n];

	return 0;
}