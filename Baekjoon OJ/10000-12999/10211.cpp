#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;

	while (tc--) {
		int N; cin >> N;

		vector<int> arr(N);
		for (int& i : arr) cin >> i;

		int ans = -INF, cur = 0;
		for (int i = 0; i < N; i++) {
			cur = max(cur + arr[i], arr[i]);
			ans = max(ans, cur);
		}

		cout << ans << '\n';
	}

	return 0;
}