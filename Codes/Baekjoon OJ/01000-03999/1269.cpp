#include <iostream>
#include <map>
using namespace std;

map<int, int> bst;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int a, b;
	cin >> a >> b;
	
	for (int i = 0; i < a; i++) {
		int x;
		cin >> x;

		bst.insert({ x, 0 });
	}

	int ans = 0;

	for (int i = 0; i < b; i++) {
		int x;
		cin >> x;

		if (bst.find(x) != bst.end()) ans++;
	}

	cout << a + b - 2 * ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ���� Ž�� Ʈ��
���� ���		: �������� ���� Ž�� Ʈ���� Ȱ���ϸ� O(lgn)�ð��� Ž�� ����.
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////