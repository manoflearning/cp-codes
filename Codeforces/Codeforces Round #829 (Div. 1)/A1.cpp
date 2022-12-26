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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		int n; cin >> n;

		vector<int> a(n + 1), b(n + 1);
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			b[i] = (i & 1 ? -1 : 1) * a[i];
		}

		// build psum
		vector<int> ps1(n + 1), ps2(n + 1);
		for (int i = 1; i <= n; i++) {
			if (i & 1) {
				if (a[i] == 1) ps1[i]++, ps2[i]--;
				if (a[i] == -1) ps1[i]--, ps2[i]++;
			}
			else {
				if (a[i] == 1) ps1[i]--, ps2[i]++;
				if (a[i] == -1) ps1[i]++, ps2[i]--;
			}
			ps1[i] += ps1[i - 1];
			ps2[i] += ps2[i - 1];
		}

		// edge case
		if (ps1[n] % 2) {
			cout << -1 << '\n';
			continue;
		}

		// edge case
		if (ps1[n] == 0) {
			cout << 1 << '\n';
			cout << 1 << ' ' << n << '\n';
			continue;
		}

		// get answer
		int val = -ps1[n] / 2;
		
		if (val < 0) { // wlog
			val = -val;
			for (int i = 1; i <= n; i++) b[i] = -b[i];
		}
		
		vector<pii> res;
		for (int i = 2; i <= n; i += 2) {
			if (b[i] == -1) continue;

			int s = i, e = i;

			int sum = b[s];
			while (e + 2 <= n && b[e + 1] > 0 && b[e + 2] >= 0) {
				if (sum + b[e + 1] + b[e + 2] > val) break;
				sum += b[e + 1] + b[e + 2];
				e = e + 2;
			}
			if (e == n - 1 && b[e + 1] > 0 && sum + b[e + 1] <= val) {
				sum += b[e + 1];
				e = e + 1;
			}
			if (sum <= val && sum > 0) {
				val -= sum;
				res.push_back({ s, e });
				i = e;
			}
		}
		
		if (val > 0) {
			cout << -1 << '\n';
			continue;
		}

		vector<pii> ans;
		ans.push_back({ 1, res.front().fr - 1 });
		for (int i = 0; i < sz(res); i++) {
			ans.push_back(res[i]);
			if (i + 1 < sz(res)) {
				ans.push_back({ res[i].sc + 1, res[i + 1].fr - 1 });
			}
		}
		if (ans.back().sc != n) ans.push_back({ ans.back().sc + 1, n });

		cout << sz(ans) << '\n';
		for (auto& i : ans)
			cout << i.fr << ' ' << i.sc << '\n';
	}

	return 0;
}