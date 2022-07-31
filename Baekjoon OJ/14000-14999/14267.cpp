#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100000;

vector<int> childNode[MAX + 1];
int hitted[MAX + 1];

void hit(int node);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m, pass;
	cin >> n >> m >> pass;
	
	for (int i = 2; i <= n; i++) {
		int parent;
		cin >> parent;

		childNode[parent].push_back(i);
	}

	for (int i = 0; i < m; i++) {
		int parent, strength;
		cin >> parent >> strength;

		hitted[parent] += strength;
	}

	for (int i = 2; i <= n; i++)
		hit(i);

	for (int i = 1; i <= n; i++)
		cout << hitted[i] << ' ';

	return 0;
}

void hit(int node) {
	for (int i = 0; i < childNode[node].size(); i++)
		hitted[childNode[node][i]] += hitted[node];
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: childNode 사용. 트리.
접근 방식		: 
결정적 깨달음		: 상사의 번호가 자신의 번호보다 작다는 점을 이용하여, O(n + m)의 알고리즘 가능.
오답 원인		: 1. O(n * m)의 시간복잡도. 시간초과
				  2. 
*/////////////////////////////////////////////////////////////////////