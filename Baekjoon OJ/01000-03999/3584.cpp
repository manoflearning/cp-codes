#include <iostream>
#include <vector>
using namespace std;

const int MAX = 10000;

int parentNode[MAX + 1];
bool visited[MAX + 1];

void parentCheck(int node);
void parentFind(int node);

int main() {
	int t;
	cin >> t;

	for (int test = 0; test < t; test++) {
		int n;
		cin >> n;

		for (int i = 0; i < n - 1; i++) {
			int parent, child;
			cin >> parent >> child;

			parentNode[child] = parent;
		}

		int a, b;
		cin >> a >> b;
		parentCheck(a);
		parentFind(b);
		//reset
		for (int i = 1; i <= n; i++) {
			visited[i] = false;
			parentNode[i] = 0;
		}

	}

	return 0;
}

void parentCheck(int node) {
	visited[node] = true;

	if (parentNode[node] != 0) parentCheck(parentNode[node]);
}
void parentFind(int node) {
	if (visited[node]) {
		cout << node << '\n';
		return;
	}

	parentFind(parentNode[node]);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 트리. parentNode를 활용.
접근 방식		: 두 노드 중 한 노드의 모든 조상을 bool형 배열로 저장. 다른 노드의 조상을 깊이가 깊은 조상부터 방문. bool형 배열에 이미 저장된 조상에 방문시 중단, 그 조상 출력.
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////