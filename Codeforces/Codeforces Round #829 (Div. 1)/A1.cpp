#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

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

		vector<int> a(n + 1);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum += a[i];
		}

		if (sum % 2) {
			cout << -1 << '\n';
			continue;
		}

		vector<pii> ans;
		for (int i = 1; i <= n; i += 2) {
			if (a[i] == a[i + 1]) {
				ans.push_back({ i, i + 1 });
			}
			else {
				ans.push_back({ i, i });
				ans.push_back({ i + 1, i + 1 });
			}
		}

		cout << sz(ans) << '\n';
		for (auto& i : ans)
			cout << i.fr << ' ' << i.sc << '\n';
	}

	return 0;
}