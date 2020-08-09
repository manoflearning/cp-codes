#include <iostream>
#include <algorithm>
using namespace std;

int find(int N, int sum, int cnt, int flag);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	int ans = find(N, 0, 0, 1);
	cout << ans << '\n';

	return 0;
}

int find(int N, int sum, int cnt, int flag) {
	if (N == sum) return cnt;
	if (cnt >= 4) return 4;

	int ret = 5;
	for (int i = flag; i * i <= N - sum; i++) {
		ret = min(ret, find(N, sum + i * i, cnt + 1, i));
	}
	return ret;
}
/*//////////////////////////////////////////////////////////////////
문제 해법		: 재귀, 수학
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////