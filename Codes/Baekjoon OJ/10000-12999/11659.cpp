#include <iostream>
using namespace std;

const int MAX = 100000;

int arr[MAX], psum[MAX + 1];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];

		psum[i + 1] = psum[i] + arr[i];
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;

		cout << psum[b + 1] - psum[a] << '\n';
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: psum
접근 방식		: psum을 활용하면 값이 변하지 않는 구간의 합을 O(1)시간에 구할 수 있다.
결정적 깨달음		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////