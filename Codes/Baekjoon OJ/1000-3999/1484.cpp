#include <iostream>
#include <cmath>
#define ll long long
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int g; cin >> g;

	ll L = 1;
	bool ans = false;
	for (ll i = 2; i <= g; i++) {
		while (i * i - L * L > g) L++;
		if (i * i - L * L == g) {
			cout << i << '\n';
			ans = true;
		}
	}

	if (!ans) cout << -1;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 투 포인터 응용
결정적 깨달음		: 
시간복잡도		: O(n)
오답 원인		: 1. 가능한 몸무게가 없을 경우를 고려하지 않음
				  2. 
*/////////////////////////////////////////////////////////////////////