#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000000;

int n, m;
vector<int> p(MAX + 1, -1);

void merge(int b, int c);
int find(int x);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 0) merge(b, c);
		if (a == 1) {
			if (find(b) == find(c)) cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}

void merge(int b, int c) {
	int B = find(b), C = find(c);

	if (B != C) p[C] = B;
}
int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ���Ͽ� ���ε�
���� ���		: ���Ͽ� ���ε��� find ������ �ð����⵵�� O(log*N)�� ����ð����� ����ص� ����.
������ ������		: ���Ͽ� ���ε��� find ���꿡�� �Ź� Ž���� �̷������ ��Ʈ ��尡 �ƴ� Ʈ���� ��带, ��Ʈ ����� �ڽ����� �����ؾ� ��. �׷��� ������ find ������ ���� �ð����⵵�� ����.
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////