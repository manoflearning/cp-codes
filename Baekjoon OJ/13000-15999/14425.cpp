#include <iostream>
#include <map>
using namespace std;

map<string, string> BST;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		string word;
		cin >> word;

		BST.insert(make_pair(word, word));
	}

	int count = 0;
	for (int i = 0; i < m; i++) {
		string word;
		cin >> word;

		map<string, string>::iterator it = BST.lower_bound(word);

		if (word == it->first) count++;
	}

	cout << count;

	return 0;
}
/*/////////////////////////////////////////////////////////////////////
문제 해법		: map 자료구조 활용. 이진 탐색 트리
접근 방식		: 
결정적 깨달음		:
오답 원인		: 1.
				  2.
*//////////////////////////////////////////////////////////////////////