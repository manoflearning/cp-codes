#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;

pair<int, string> member[MAX];

bool compare(pair<int, string> a, pair<int, string> b);

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> member[i].first >> member[i].second;

	stable_sort(member, member + n, compare);

	for (int i = 0; i < n; i++)
		cout << member[i].first << ' ' << member[i].second << '\n';

	return 0;
}

bool compare(pair<int, string> a, pair<int, string> b) {
	if (a.first == b.first) return false;
	
	return a.first < b. first;
}
/*/////////////////////////////////////////////////////////////////////
���� �ع�		: 
���� ���		: 
������ ������		:
���� ����		: 1.
				  2.
*//////////////////////////////////////////////////////////////////////