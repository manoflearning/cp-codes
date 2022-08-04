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
���� �ع�		: Ʈ��. parentNode�� Ȱ��.
���� ���		: �� ��� �� �� ����� ��� ������ bool�� �迭�� ����. �ٸ� ����� ������ ���̰� ���� ������� �湮. bool�� �迭�� �̹� ����� ���� �湮�� �ߴ�, �� ���� ���.
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////