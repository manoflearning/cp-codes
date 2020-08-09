#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;

void backtrack();

int main() {
	cin >> n >> m;

	backtrack();
	
	return 0;
}

void backtrack() {
	//base case
	if (arr.size() == m) {
		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << ' ';
		cout << '\n';

		return;
	}

	for (int i = 1; i <= n; i++) {
		arr.push_back(i);
		backtrack();
		arr.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ��Ʈ��ŷ
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////