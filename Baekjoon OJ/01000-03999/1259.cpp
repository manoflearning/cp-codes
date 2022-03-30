#include <iostream>
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (true) {
		string s; cin >> s;

		if (s == "0") break;

		bool yes = true;
		for (int i = 0; i < s.size() / 2; i++) {
			if (s[i] != s[s.size() - 1 - i]) {
				yes = false;
				break;
			}
		}

		if (yes) cout << "yes\n";
		else cout << "no\n";
	}

	return 0;
}
/*//////////////////////////////////////////////////////////////////
���� �ع�		: 
������ ������		:
�ð����⵵		: O(n)
���� ����		: 1.
				  2.
*///////////////////////////////////////////////////////////////////