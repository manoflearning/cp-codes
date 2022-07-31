#include <iostream>
#include <vector>
using namespace std;

int erase;
vector<int> childNode[50];

int countLeafNode(int node);

int main() {
	int n;
	cin >> n;

	int root;

	for (int i = 0; i < n; i++) {
		int parent;
		cin >> parent;

		if (parent == -1) root = i;
		else childNode[parent].push_back(i);
	}

	cin >> erase;

	cout << countLeafNode(root);
	
	return 0;
}

int countLeafNode(int node) {
	//base case
	if (node == erase) return 0;
	if (childNode[node].size() == 0) return 1;

	int ret = 0;

	for (int i = 0; i < childNode[node].size(); i++) {
		if (childNode[node][i] == erase) {
			if (childNode[node].size() == 1) ret += 1;
			
			continue;
		}
		ret += countLeafNode(childNode[node][i]);
	}
	
	return ret;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 배열을 활용한 트리 구현.
접근 방식		: childNode 정보만 저장함. 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////