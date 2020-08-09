#include <iostream>
#define ll long long
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string A, B;
	cin >> A >> B;

	ll ans = 0;
	for (char a : A) {
		for (char b : B) {
			ans += (a - '0') * (b - '0');
		}
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		: 
시간복잡도		: O(|A| * |B|)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////