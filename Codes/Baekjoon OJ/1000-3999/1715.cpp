#include <iostream>
#include <queue>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	priority_queue<int, vector<int>, greater<int>> pq;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		pq.push(x);
	}

	int ans = 0;

	while (pq.size() > 1) {
		int a = pq.top();
		pq.pop();
		int b = pq.top();
		pq.pop();

		ans += a + b;

		pq.push(a + b);
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 우선순위 큐
접근 방식		: 시간복잡도 O(n * lgn)
결정적 깨달음		: 
오답 원인		: 1. 메모리 초과
				  2. 
*/////////////////////////////////////////////////////////////////////