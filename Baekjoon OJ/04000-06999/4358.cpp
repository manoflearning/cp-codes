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
���� �ع�		: ���� Ž�� Ʈ���� ����, Ž���� �ſ� �����ٴ� ���� �̿�.
���� ���		: �Է����� ������ �̸��� Ʈ���� �����Ѵٸ�, Ʈ���� value ���� ++��. �ƴ϶�� �̸��� Ʈ���� �߰�.
������ ������		:
���� ����		: 1. ���鹮�� �����ؼ� �Է¹ޱ� ���ؼ� <string> ��������� getline�� �����.
				  2. 
*/////////////////////////////////////////////////////////////////////