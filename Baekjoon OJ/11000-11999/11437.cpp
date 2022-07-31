#include <iostream>
#include <vector>
using namespace std;

const int MAX = 50000;

vector<int> tree[MAX + 1];
int parentNode[MAX + 1];
int depth[MAX + 1];

void calDepth(int node, int visited, int count);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int node1, node2;
		cin >> node1 >> node2;

		tree[node1].push_back(node2);
		tree[node2].push_back(node1);
	}

	calDepth(1, 0, 1);

	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int node1, node2;
		cin >> node1 >> node2;

		while (depth[node1] != depth[node2]) {
			if (depth[node1] > depth[node2]) node1 = parentNode[node1];
			else node2 = parentNode[node2];
		}

		while (node1 != node2) {
			node1 = parentNode[node1];
			node2 = parentNode[node2];
		}

		cout << node1 << '\n';
	}

	return 0;
}

void calDepth(int node, int visited, int count) {
	depth[node] = count;

	for (int i = 0; i < tree[node].size(); i++) {
		if (tree[node][i] == visited) continue;

		parentNode[tree[node][i]] = node;
		calDepth(tree[node][i], node, count + 1);
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: Lowest Common Ancester
접근 방식		: 공통 조상을 찾을 두 정점의 깊이를 일치하게 만든다. 한 단계를 둘 다 올려본다.
결정적 깨달음		: 트리의 루트 노드를 안다는 가정 하에, 트리의 깊이와 부모-자식 관계를 명확히 하는 데에는 O(n)의 시간이 걸림.
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////