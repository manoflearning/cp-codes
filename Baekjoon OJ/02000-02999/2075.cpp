#include <iostream>
#include <queue>
using namespace std;

int n;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		pq.push(x);
	}
	for (int i = 0; i < n - 1; i++) {
		for (int l = 0; l < n; l++) {
			int x;
			cin >> x;

			pq.push(x);
		}
		for (int l = 0; l < n; l++)
			pq.pop();
	}

	cout << pq.top();

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 우선순위 큐
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////