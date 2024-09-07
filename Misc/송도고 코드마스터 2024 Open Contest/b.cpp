// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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

int n, k, T0;
ll d[1010];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k >> T0;
    for (int i = 1; i <= n; i++) cin >> d[i];

    ll ans = 0;
    ll T_prv = T0;
    for (int i = 1; i <= n; i++) {
        ll T_now = T_prv + d[i] + abs(T_prv - k) * (T_prv < k ? 1 : -1);
        ans += abs(T_now - k);
        // cout << T_now << '\n';
        T_prv = T_now;
    }

    cout << ans;
}
