#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

struct xyr {
	int x, y, r;
};
struct nnd {
	int n1, n2;
	double d;
};

int W, N, p[1005];
vector<xyr> S;
vector<nnd> E;

bool cmp(nnd a, nnd b) {
	return a.d < b.d;
}
double dist(int u, int v);
int find(int x);
void merge(int u, int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed; cout.precision(6);

	int T; cin >> T;

	while (T--) {
		//reset
		memset(p, -1, sizeof(p));
		E.clear(); S.clear();

		//�׽�Ʈ���̽� ����
		cin >> W >> N;

		S.resize(N);

		for (int i = 0; i < N; i++)
			cin >> S[i].x >> S[i].y >> S[i].r;

		//������ ���� ���� ����
		for (int u = 0; u < S.size(); u++) {
			for (int v = u + 1; v < S.size(); v++) {
				E.push_back({ u, v, dist(u, v) });
			}
		}

		//���� ���� ���� ����
		for (int u = 0; u < S.size(); u++) {
			E.push_back({ u, N, (double)max(0, S[u].x - S[u].r) });
			E.push_back({ u, N + 1, (double)max(0, W - (S[u].x + S[u].r)) });
		}

		//���� �� ���� ����
		E.push_back({ N, N + 1, (double)W });

		//�������� ����ġ�� �������� �������� ����
		sort(E.begin(), E.end(), cmp);

		double ans = 0;
		for (int i = 0; i < E.size(); i++) {
			if (find(E[i].n1) == find(E[i].n2)) continue;
			ans = max(ans, E[i].d);
			merge(E[i].n1, E[i].n2);
			if (find(N) == find(N + 1)) break;
		}

		//�������̹Ƿ� 2�� �����ش�
		cout << ans / 2 << '\n';
	}

	return 0;
}

double dist(int u, int v) {
	double d = sqrt(pow(S[u].x - S[v].x, 2) + pow(S[u].y - S[v].y, 2));
	return max((double)0, d - (S[u].r + S[v].r));
}
int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int u, int v) {
	int U = find(u), V = find(v);
	if (U == V) return;
	p[U] += p[V];
	p[V] = U;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ũ�罺Į �˰�����
������ ������		: 
�ð����⵵		: 
���� ����		: 1. ���� �� ���� ������ �߰����� ���� (������ ������ 0�� ��� Ʋ��)
				  2. 
*/////////////////////////////////////////////////////////////////////