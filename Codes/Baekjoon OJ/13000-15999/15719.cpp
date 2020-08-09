#include <iostream>
using namespace std;

const int MAX = 1e7;

bool exist[MAX + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	int ans;
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		if (exist[x]) ans = x;
		exist[x] = true;
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: 
������ ������		: 
�ð����⵵		: O(n)
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////