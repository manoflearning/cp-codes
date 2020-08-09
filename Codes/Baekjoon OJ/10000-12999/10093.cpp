#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	ll A, B; cin >> A >> B;

	if (A > B) swap(A, B);

	cout << max((ll)0, B - A - 1) << '\n';
	for (ll i = A + 1; i < B; i++)
		cout << i << ' ';

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		:
시간복잡도		: 
오답 원인		: 1. 오버플로우.. 진짜 재정신 아니네
				  2.
*/////////////////////////////////////////////////////////////////////