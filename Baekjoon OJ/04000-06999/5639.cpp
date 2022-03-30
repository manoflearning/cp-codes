#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 10000;

int preorder[MAX + 1];

void printPostorder(int start, int end);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n = 0;

	while (cin >> preorder[n]) n++;

	printPostorder(0, n - 1);

	return 0;
}

void printPostorder(int start, int end) {
	//base case
	if (start > end) return;
	
	int root = preorder[start];

	int flag;
	for (flag = start + 1; flag <= end; flag++)
		if (preorder[flag] > root) break;

	printPostorder(start + 1, flag - 1);
	printPostorder(flag, end);
	cout << root << '\n';
}
/*//////////////////////////////////////////////////////////////////////
���� �ع�		: eof Ȱ��, ���
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////