#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> p(201, -1);

int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//�Է� �� merge ������ Ȱ���ؼ� ���� Ʈ�� �����
	cin >> n >> m;

	for (int c1 = 1; c1 <= n; c1++) {
		for (int c2 = 1; c2 <= n; c2++) {
			int x;
			cin >> x;

			if (x == 1) merge(c1, c2);
		}
	}
	//
	int wannaGo[1000];
	for (int i = 0; i < m; i++)
		cin >> wannaGo[i];

	bool ans = true;
	for (int i = 0; i < m - 1; i++)
		if (find(wannaGo[i]) != find(wannaGo[i + 1])) {
			ans = false;
			break;
		}

	if (ans) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}

int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A != B) p[B] = A;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ���Ͽ� ���ε�
���� ���		: �Է��� ���� �� union ���� Ȱ��(�ڵ忡�� merge�Լ�). ���� ���θ� find �������� �Ǵ�.
������ ������		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////