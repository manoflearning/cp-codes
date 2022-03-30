#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;

void backtrack(int flag);

int main() {
	cin >> n >> m;

	backtrack(0);

	return 0;
}

void backtrack(int flag) {
	//base case
	if (arr.size() == m) {
		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << ' ';
		cout << '\n';

		return;
	}

	for (int i = flag + 1; i <= n; i++) {
		arr.push_back(i);
		backtrack(i);
		arr.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ��Ʈ��ŷ
���� ���		: ������� ���� �� �� ���� ū ���� ����. �� ������ ū ���� ���� Ž�� ����
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////