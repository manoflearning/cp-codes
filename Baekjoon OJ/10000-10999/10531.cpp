//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

int n, m;
vector<int> a;
int vi[202020], dp[202020];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

	cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
    sort(all(a));
    a.erase(unique(all(a)), a.end());

    for (auto& i : a) {
        dp[i] = vi[i] = 1;
        if (i * 2 < 202020) dp[i * 2] = 1;
    }

    cin >> m;
    int ans = 0;
    while (m--) {
        int v; cin >> v;
        if (dp[v] != -1) {
            ans += dp[v];
            continue;
        }

        int bit = 0;
        for (int i = upper_bound(all(a), v) - a.begin() - 1; i >= 0; i--) {
            int x = a[i];
            if (x < v - x) break;
            if (vi[v - x]) { bit = 1; break; }
        }
        dp[v] = bit;
        ans += dp[v];
    }

    cout << ans;

	return 0;
}