#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000000001;

vector<int> sgtr;

int MIN(int L, int R, int node, int nodeL, int nodeR);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//
	int n, m, flag;
	cin >> n >> m;

	for (flag = 1; flag < n; flag *= 2);
	sgtr.resize(flag * 2, MAX);

	for (int i = flag; i < flag + n; i++)
		cin >> sgtr[i];
	//construct
	for (int i = flag - 1; i >= 1; i--)
		sgtr[i] = min(sgtr[2 * i], sgtr[2 * i + 1]);

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		cout << MIN(a, b, 1, 1, flag) << '\n';
	}

	return 0;
}

int MIN(int L, int R, int node, int nodeL, int nodeR) {
	if (R < nodeL || nodeR < L) return MAX;
	if (L <= nodeL && nodeR <= R) return sgtr[node];
	
	int mid = (nodeL + nodeR) / 2;
	return min(MIN(L, R, 2 * node, nodeL, mid), MIN(L, R, 2 * node + 1, mid + 1, nodeR));
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ����Ʈ��
���� ���		: ����Ʈ���� Ȱ���ϸ� �迭�� Ư�� ������ �ּڰ��� O(lgn)�� �ð����⵵�� ã�� �� ����.
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////