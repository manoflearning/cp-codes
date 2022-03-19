#include <iostream>
#include <algorithm>
using namespace std;

int GCD(int a, int b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, M; 
	cin >> N >> M;

	int gcd = GCD(N, M);

	cout << M - gcd;

	return 0;
}

int GCD(int a, int b) {
	if (b == 0) return a;
	return GCD(b, a % b);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: gcd
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////