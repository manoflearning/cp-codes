#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int arr[10000], ans[10000];
priority_queue<int> pqMIN;
priority_queue<int, vector<int>, greater<int>> pqMAX;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for (int test = 0; test < t; test++) {
		//reset
		while (!pqMIN.empty()) pqMIN.pop();
		while (!pqMAX.empty()) pqMAX.pop();
		//input
		int m, mid;
		cin >> m;

		for (int i = 1; i <= m; i++)
			cin >> arr[i];
		//output
		cout << (m + 1) / 2 << '\n';

		ans[1] = arr[1];

		if (3 <= m) {
			//1 ~ 3
			pqMIN.push(min(arr[1], min(arr[2], arr[3])));
			pqMAX.push(max(arr[1], max(arr[2], arr[3])));
			for (int i = 1; i <= 3; i++) {
				if (arr[i] != pqMIN.top() && arr[i] != pqMAX.top())
					mid = arr[i];
			}
			//�ߺ� ���� ó��
			for (int i = 1; i <= 3; i++) {
				for (int l = i + 1; l <= 3; l++) {
					if (arr[i] == arr[l])
						mid = arr[i];
				}
			}

			ans[3] = mid;
			//4 ~
			for (int i = 4; i <= m; i++) {
				if (i % 2 == 0) {
					if (arr[i] < mid) {
						pqMIN.push(arr[i]);
						pqMAX.push(mid);
					}
					else {
						pqMIN.push(mid);
						pqMAX.push(arr[i]);
					}
				}
				else {
					if (arr[i] < pqMIN.top()) {
						mid = pqMIN.top();
						pqMIN.pop();
						pqMIN.push(arr[i]);
					}
					else if (arr[i] <= pqMAX.top()) {
						mid = arr[i];
					}
					else {
						mid = pqMAX.top();
						pqMAX.pop();
						pqMAX.push(arr[i]);
					}
					ans[i] = mid;
				}
			}
		}

		for (int i = 1; i <= m; i += 2) {
			cout << ans[i] << ' ';
			if ((i + 1) / 2 % 10 == 0) cout << '\n';
		}
		if ((m + 1) / 2 % 10 != 0) cout << '\n';
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �켱���� ť
���� ���		: �ִ� �켱���� ť�� �ּ� �켱���� ť �ΰ��� ����. �Է��� ���ȿ� ���� �� ť�� ũ�⸦ �����ϰ� �����ϸ鼭, ���� �ϳ��� ���� ��.
������ ������		:  
���� ����		: 1. ������ �ߺ��� ���� ���ԵǾ� ���� ��츦 �������� ����.
				  2. 
*/////////////////////////////////////////////////////////////////////