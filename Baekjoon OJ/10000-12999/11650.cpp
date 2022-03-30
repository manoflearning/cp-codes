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
���� �ع�		: sort �Լ� ���. compare �Լ� ����
���� ���		: 
������ ������		:
���� ����		: 1.
				  2.
*//////////////////////////////////////////////////////////////////////