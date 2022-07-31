#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, int> BST;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(4);

	double all = -1;
	while (!cin.eof()) {
		string tree;
		getline(cin, tree);

		map<string, int>::iterator it = BST.lower_bound(tree);

		if (it != BST.end() && it->first == tree) it->second++;
		else BST.insert(make_pair(tree, 1));

		all++;
	}

	map<string, int>::iterator it = BST.begin();
	it++;
	while (it != BST.end()) {
		cout << it->first << ' ' << it->second / all * 100 << '\n';
		it++;
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 이진 탐색 트리가 삽입, 탐색이 매우 빠르다는 점을 이용.
접근 방식		: 입력으로 들어오는 이름이 트리에 존재한다면, 트리의 value 값을 ++함. 아니라면 이름을 트리에 추가.
결정적 깨달음		:
오답 원인		: 1. 공백문자 포함해서 입력받기 위해선 <string> 헤더파일의 getline을 써야함.
				  2. 
*/////////////////////////////////////////////////////////////////////