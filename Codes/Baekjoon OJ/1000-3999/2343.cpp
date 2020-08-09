#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1e5;

int N, M, cost[MAX + 5];

int lower_bound(int L, int R);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> N >> M;

	int L = 0, R = 0;
	for (int i = 0; i < N; i++) {
		cin >> cost[i];
		L = max(L, cost[i]);
		R += cost[i];
	}
	
	cout << lower_bound(L, R);
	
	return 0;
}

int lower_bound(int L, int R) {
	//base case
	if (L == R) return L;

	int mid = (L + R) / 2;
	
	int money = mid, cnt = 1;
	for (int i = 0; i < N; i++) {
		if (money >= cost[i]) money -= cost[i];
		else {
			money = mid - cost[i];
			cnt++;
		}
	}

	if (cnt <= M) return lower_bound(L, mid);
	else return lower_bound(mid + 1, R);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 이분 탐색(lower bound)
결정적 깨달음		: lower bound는 탐색 원소를 기준으로 왼쪽은 조건 불만족, 자신을 포함한 오른쪽은 모두 조건 만족여야 한다.
시간복잡도		: O(nlg(10^11))
오답 원인		: 1. 1e11는 int형 범위 밖이다..
				  2. 
*/////////////////////////////////////////////////////////////////////