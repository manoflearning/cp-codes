#include <iostream>
#include <cmath>
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	//첫 번째 라운드
	int round1 = 0;
	for (int i = 0; i < N; i++) {
		int x;  cin >> x;
		round1 += fabs(x);
	}

	//두 번째 라운드
	int round2 = 0;
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		round2 -= fabs(x);
	}

	//출력
	cout << round1 - round2;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////