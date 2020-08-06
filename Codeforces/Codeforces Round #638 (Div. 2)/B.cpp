#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
using namespace std;

const int INF = 1e9 + 7;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		int N, K;
		cin >> N >> K;

		vector<int> arr(N + 5), ans;
		vector<bool> exist(N + 5);
		int cnt = 0, mn = INF, mx = -1;
		for (int i = 1; i <= N; i++) {
			cin >> arr[i];
			mn = min(mn, arr[i]);
			mx = max(mx, arr[i]);
			if (!exist[arr[i]]) {
				exist[arr[i]] = true;
				cnt++;
				ans.push_back(arr[i]);
			}
		}

		if (cnt > K) cout << -1 << '\n';
		else {
			for (int i = 1; i <= N; i++) {
				if (ans.size() >= K) break;
				if (!exist[i]) ans.push_back(i);
			}

			cout << N * K << '\n';
			for (int i = 0; i < N; i++) {
				for (int x : ans) cout << x << ' ';
			}
			cout << '\n';
		}
		/*if ((mx - mn + 1) > K) cout << -1 << '\n';
		else {
			K -= (mx - mn + 1);
			while (K > 0) {
				if (mx < N) mx++;
				else if (1 < mn) mn--;
				K--;
			}
			cout << N * (mx - mn + 1) << '\n';
			for (int i = 0; i < N; i++) {
				for (int l = mn; l <= mx; l++) {
					cout << l << ' ';
				}
			}
			cout << '\n';
		}*/
	}

	return 0;
}