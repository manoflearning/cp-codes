#include <iostream>
#include <map>
using namespace std;

int g, p;
map<int, int, greater<int>> mp;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> g >> p;

	for (int i = 1; i <= g; i++)
		mp.insert({ i, 0 });
	//
	int ans = 0;
	for (int i = 0; i < p; i++) {
		int x;
		cin >> x;

		map<int, int>::iterator it = mp.lower_bound(x);
		if (it != mp.end()) {
			mp.erase(it);
			ans++;
		}
		else break;
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ���� Ž�� Ʈ��
���� ���		: �ð����⵵ O( g*lgg + p * lgp);
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////