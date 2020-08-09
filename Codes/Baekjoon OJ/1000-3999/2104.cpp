#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int MAX = 1e5;

int N;
ll A[MAX + 5];

ll find_max(int L, int R);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> A[i];

	cout << find_max(1, N);
	
	return 0;
}

ll find_max(int L, int R) {
	//base case
	if (L == R) return A[L] * A[L];
	if (L > R) return 0;

	int mid = (L + R) / 2;
	//최대의 점수를 갖는 부분배열이 mid번째 배열 원소를 포함하는 않는 모든 경우
	ll ret = max(find_max(L, mid - 1), find_max(mid + 1, R));

	//최대의 점수를 갖는 부분배열이 mid번째 배열 원소를 포함하는 모든 경우
	ll sum = A[mid], mul = A[mid];
	int mL = mid, mR = mid;

	ret = max(ret, sum * mul);
	while (!(L == mL && mR == R)) {
		if (L == mL || (mR != R && A[mL - 1] <= A[mR + 1])) {
			mR++;
			sum += A[mR];
			mul = min(mul, A[mR]);
		}
		else {
			mL--;
			sum += A[mL];
			mul = min(mul, A[mL]);
		}

		ret = max(ret, sum * mul);
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 분할정복
결정적 깨달음		: 
시간복잡도		: 한 번의 함수 호출에서 O(R - L). 함수의 (R - L)이 2배로 작아짐에 따라 함수 호출은 2배로 늘어남. 함수의 (R - L)은 최소 1임. 따라서 O(nlgn).
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////