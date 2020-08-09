#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;

vector<pair<int, int>> dot;

bool compare(pair<int, int> a, pair<int, int> b);

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;

		dot.push_back(make_pair(x, y));
	}

	sort(dot.begin(), dot.end(), compare);

	for (int i = 0; i < n; i++)
		cout << dot[i].first << ' ' << dot[i].second << '\n';

	return 0;
}

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first) {
		return a.first < b.first;
	}
	else return a.second < b.second;
}
/*/////////////////////////////////////////////////////////////////////
문제 해법		: sort 함수 사용. compare 함수 구현
접근 방식		: 
결정적 깨달음		:
오답 원인		: 1.
				  2.
*//////////////////////////////////////////////////////////////////////