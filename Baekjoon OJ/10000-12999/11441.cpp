#include <iostream>
using namespace std;

const int MAX = 100000;

int psum[MAX + 1];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;

		psum[i] = x + psum[i - 1];
	}

	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int s, e;
		cin >> s >> e;

		cout << psum[e] - psum[s - 1] << '\n';
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: prefix sum
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////