#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	string cal;
	cin >> cal;

	string porm;
	vector<int> num;

	int st = 0;
	for (int i = 0; i < cal.size(); i++) {
		if (cal[i] == '+' || cal[i] == '-') {
			num.push_back(stoi(cal.substr(st, i)));
			st = i + 1;
			porm.push_back(cal[i]);
		}
	}
	num.push_back(stoi(cal.substr(st, cal.size())));

	int ans = num[0];
	int flag = 0;
	
	while (flag < porm.size() && porm[flag] == '+') {
		ans += num[flag + 1];
		flag++;
	}
	while (flag < porm.size()) {
		ans -= num[flag + 1];
		flag++;
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 그리디 알고리즘
접근 방식		: - 연산자가 처음 나오면, 그 뒤로는 모든 수를 다 뺀다. 그 전에는 모든 수를 다 더한다
결정적 깨달음		: stoi 함수를 활용하여 문자열형을 정수형으로 바꿀 수 있다.
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////