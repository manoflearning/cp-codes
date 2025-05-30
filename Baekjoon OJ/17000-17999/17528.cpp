//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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

int n, dp[255][255 * 255];
pii a[255];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> a[i].fr >> a[i].sc;
    
    for (int i = 0; i < 255; i++)
        for (int j = 0; j < 255 * 255; j++) dp[i][j] = INF;

    dp[1][0] = a[1].sc;
    dp[1][a[1].fr] = 0;

    for (int v = 1; v < n; v++) {
        for (int i = 0; i < 255 * 255; i++) {
            if (dp[v][i] == INF) continue;
            dp[v + 1][i] = min(dp[v + 1][i], dp[v][i] + a[v + 1].sc);
            dp[v + 1][i + a[v + 1].fr] = min(dp[v + 1][i + a[v + 1].fr], dp[v][i]);
        }
    }

    int ans = INF;
    for (int i = 0; i < 255 * 255; i++) {
        ans = min(ans, max(dp[n][i], i));
    }
    
    cout << ans;

	return 0;
}