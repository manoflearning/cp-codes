#include <iostream>
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		int n; cin >> n;

		int sum = 0;
		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			sum += x;
		}

		if (sum == 0) cout << "Equilibrium\n";
		else if (sum > 0) cout << "Right\n";
		else cout << "Left\n";
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		: 이 문제 구데기
시간복잡도		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////