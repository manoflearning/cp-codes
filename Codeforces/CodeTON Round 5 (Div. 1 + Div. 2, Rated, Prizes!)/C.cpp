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

int n, a[202020];
vector<int> b[202020];
int dp[202020], dp2[202020];

void init() {
    for (int i = 1; i <= n; i++) {
        a[i] = 0;
        b[i].clear();
        dp[i] = dp2[i] = 0;
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        for (int i = 1; i <= n; i++) 
            b[a[i]].push_back(i);

        // dp
        dp[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
            dp[i] = dp[i + 1];

            vector<int>& arr = b[a[i]];
            int idx = lower_bound(arr.begin(), arr.end(), i) - arr.begin();
            if (idx == sz(arr) - 1) continue;

            int j = arr[idx + 1];
            dp2[a[i]] = max(j - i + dp2[a[i]], (j - i + 1) + dp[j + 1]);
            dp[i] = max(dp[i], dp2[a[i]]);

            /*for (int j = idx + 1; j < sz(arr); j++) {
                int k = arr[j];
                dp[i] = max(dp[i], (k - i + 1) + dp[k + 1]);
            }*/
        }

        cout << dp[1] << '\n';
	}
}