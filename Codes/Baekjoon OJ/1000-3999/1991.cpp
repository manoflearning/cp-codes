#include <iostream>
using namespace std;

char tree[26][2];

void preorder(char root);
void inorder(char root);
void postorder(char root);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for (int test = 0; test < t; test++) {
		char root, left, right;
		cin >> root >> left >> right;

		tree[root - 'A'][0] = left;
		tree[root - 'A'][1] = right;
	}
	
	preorder('A');
	cout << '\n';
	inorder('A');
	cout << '\n';
	postorder('A');
	cout << '\n';

	return 0;
}

void preorder(char root) {
	//base case
	if (root == '.') return;

	cout << root;
	preorder(tree[root - 'A'][0]);
	preorder(tree[root - 'A'][1]);
}
void inorder(char root) {
	//base case
	if (root == '.') return;

	inorder(tree[root - 'A'][0]);
	cout << root;
	inorder(tree[root - 'A'][1]);
}
void postorder(char root) {
	//base case
	if (root == '.') return;

	postorder(tree[root - 'A'][0]);
	postorder(tree[root - 'A'][1]);
	cout << root;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 재귀 호출을 활용한 트리 순회
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////