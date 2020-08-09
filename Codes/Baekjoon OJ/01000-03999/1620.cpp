#include <iostream>
#include <map>
#include <string>
using namespace std;

const int MAX = 100000;

string arr[MAX + 1];
map<string, int> bst;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		cin >> arr[i];

		bst.insert({ arr[i], i });
	}

	for (int i = 0; i < m; i++) {
		string name;
		cin >> name;

		if ('0' <= name[0] && name[0] <= '9') {
			int num = stoi(name);

			cout << arr[num] << '\n';
		}
		else {
			map<string, int>::iterator it = bst.find(name);

			cout << it->second << '\n';
		}
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ���� Ž�� Ʈ��
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////