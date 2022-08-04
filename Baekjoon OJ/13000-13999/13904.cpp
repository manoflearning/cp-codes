#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> arr[1001];
priority_queue<int, vector<int>> pq;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int d, w; 
		cin >> d >> w;
		arr[d].push_back(w);
	}

	int ans = 0;

	for (int i = 1000; i >= 1; i--) {
		for (int l = 0; l < arr[i].size(); l++)
			pq.push(arr[i][l]);
		
		if (!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �켱���� ť, �׸���
���� ���		:
������ ������		:
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////