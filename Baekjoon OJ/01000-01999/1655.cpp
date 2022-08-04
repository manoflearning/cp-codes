#include <iostream>
#include <queue>
using namespace std;

int mid;
priority_queue<int> L;
priority_queue<int, vector<int>, greater<int>> R;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	//ù ��° ����
	cin >> mid;
	cout << mid << '\n';
	L.push(mid);
	
	if (N == 1) return 0;
	
	//�� ��° ����
	cin >> mid;
	if (L.top() <= mid) {
		cout << L.top() << '\n';
		R.push(mid);
	}
	else {
		cout << mid << '\n';
		R.push(L.top());
		L.pop();
		L.push(mid);
	}

	//3��° ~ N��° ����
	for (int i = 3; i <= N; i++) {
		cin >> mid;
		if (i % 2 == 1) {
			if (L.top() <= mid && mid <= R.top()) {
				cout << mid << '\n';
				L.push(mid);
			}
			else if (mid < L.top()) {
				cout << L.top() << '\n';
				L.push(mid);
			}
			else {
				cout << R.top() << '\n';
				L.push(R.top());
				R.pop();
				R.push(mid);
			}
		}
		else {
			if (L.top() <= mid) {
				cout << L.top() << '\n';
				R.push(mid);
			}
			else {
				R.push(L.top());
				L.pop();
				L.push(mid);
				cout << L.top() << '\n';
			}
		}
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �켱���� ť
������ ������		:
�ð����⵵		: O(nlgn)
���� ����		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////