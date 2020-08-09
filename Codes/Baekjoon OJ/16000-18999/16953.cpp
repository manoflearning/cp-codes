#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int INF = 1e9 + 7;

ll A, B;

int find_min(ll x, int cnt);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> A >> B;

	int ans = find_min(A, 0);

	if (ans == INF) cout << -1 << endl;
	else cout << ans + 1 << endl;

	return 0;
}

int find_min(ll x, int cnt) {
	if (x == B) return cnt;
	if (x > B) return INF;

	return min(find_min(2 * x, cnt + 1), find_min(10 * x + 1, cnt + 1));
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		: 
시간복잡도		: O(2^30)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////