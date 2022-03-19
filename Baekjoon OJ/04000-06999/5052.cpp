#include <iostream>
#include <map>
using namespace std;

map<string, string> phoneNum;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for (int test = 0; test < t; test++) {
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			string num;
			cin >> num;

			phoneNum.insert(make_pair(num, num));
		}

		bool ans = true;

		map<string, string>::iterator it1 = phoneNum.begin(), it2 = it1;
		it2++;
		
		while (it2 != phoneNum.end()) {
			if (it1->first.size() <= it2->first.size()) {
				if (it2->first.substr(0, it1->first.size()) == it1->first) ans = false;
			}
			it1++, it2++;
		}

		if (ans) cout << "YES\n";
		else cout << "NO\n";

		//reset
		phoneNum.clear();
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: BST
접근 방식		: BST로 저장했을 때 정렬이 된다는 점을 이용, O(n)시간에 일관성 탐색 (정렬된 배열을 사용해도 될듯)
결정적 깨달음		: 
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////