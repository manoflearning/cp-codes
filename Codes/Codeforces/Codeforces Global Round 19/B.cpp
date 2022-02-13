#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vs vector<string>
#define vvs vector<vector<string>>
#define fr first
#define sc second

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;

	while (tc--) {
		int n; cin >> n;

		vi a(n);
		for (auto& i : a) cin >> i;

		ll ans = 0;
		for (ll i = 1; i <= n; i++) ans += i * (n - i + 1);
		
		for (ll i = 0; i < n; i++) {
			if (a[i]) continue;
			ans += (i + 1) * (n - i);
		}

		cout << ans << '\n';

		/*sort(a.begin(), a.end());

		int ans = 0;
		if (!a[0]) {
			for (int i = 0; i < n - 1; i++) {
				if (a[i] + 1 < a[i + 1]) break;
				ans++;
			}
		}
		
		cout << (int)pow(2, n) + ans << '\n';*/
	}

	return 0;
}
