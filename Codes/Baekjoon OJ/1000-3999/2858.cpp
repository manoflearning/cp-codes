#include <iostream>
#define ll long long
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int R, B;
	cin >> R >> B;

	int sum = R + B;

	for (ll W = 1; W <= sum; W++) {
		if (sum % W != 0) continue;

		ll L = sum / W;
		if ((L - 2) * (W - 2) == B) {
			cout << L << ' ' << W;
			break;
		}
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 구현, 수학
결정적 깨달음		: 
시간복잡도		: O(R + B)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////