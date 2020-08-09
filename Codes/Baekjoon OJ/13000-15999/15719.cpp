#include <iostream>
using namespace std;

const int MAX = 1e7;

bool exist[MAX + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	int ans;
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		if (exist[x]) ans = x;
		exist[x] = true;
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		: 
시간복잡도		: O(n)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////