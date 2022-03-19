#include <iostream>
#include <vector>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;

struct lz {
	ll X;
	ll Y;
};

int flag;
vector<ll> sgtr;
vector<lz> lazy;

ll print(int L, int R, int n, int nL, int nR);
void update(int L, int R, int n, int nL, int nR, int X, int Y, int type);
void lazyCheck(int n, int nL, int nR);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;

	for (flag = 1; flag < n; flag *= 2);
	sgtr.resize(2 * flag);
	lazy.resize(2 * flag);

	for (int i = flag; i < flag + n; i++)
		cin >> sgtr[i];
	for (int i = flag - 1; i >= 1; i--)
		sgtr[i] = (sgtr[2 * i] + sgtr[2 * i + 1]) % MOD;
	for (int i = 1; i < flag + n; i++)
		lazy[i].X = 1;
	//
	int m; cin >> m;

	while (m--) {
		int a, x, y, v;
		cin >> a >> x >> y;

		if (a != 4) {
			cin >> v;
			switch (a) {
			case 1:
				update(x, y, 1, 1, flag, 1, v, a);
				break;
			case 2:
				update(x, y, 1, 1, flag, v, 0, a);
				break;
			case 3:
				update(x, y, 1, 1, flag, 0, v, a);
				break;
			}
		}
		else {
			cout << print(x, y, 1, 1, flag) << '\n';
		}
	}

	return 0;
}

ll print(int L, int R, int n, int nL, int nR) {
	lazyCheck(n, nL, nR);

	if (R < nL || nR < L) return 0;
	if (L <= nL && nR <= R) return sgtr[n];

	int mid = (nL + nR) / 2;
	return (print(L, R, 2 * n, nL, mid) + print(L, R, 2 * n + 1, mid + 1, nR)) % MOD;
}
void update(int L, int R, int n, int nL, int nR, int X, int Y, int type) {
	lazyCheck(n, nL, nR);

	if (R < nL || nR < L) return;
	if (L <= nL && nR <= R) {
		lazy[n].X *= X; lazy[n].X %= MOD;
		lazy[n].Y *= X; lazy[n].Y %= MOD;
		lazy[n].Y += Y; lazy[n].Y %= MOD;
		lazyCheck(n, nL, nR);
		return;
	}

	int mid = (nL + nR) / 2;
	update(L, R, 2 * n, nL, mid, X, Y, type);
	update(L, R, 2 * n + 1, mid + 1, nR, X, Y, type);

	sgtr[n] = (sgtr[2 * n] + sgtr[2 * n + 1]) % MOD;
}
void lazyCheck(int n, int nL, int nR) {
	if (lazy[n].X == 1 && lazy[n].Y == 0) return;

	sgtr[n] = (lazy[n].X * sgtr[n] + lazy[n].Y * (nR - nL + 1)) % MOD;
	if (n < flag) {
		lazy[2 * n].X *= lazy[n].X; lazy[2 * n].X %= MOD;
		lazy[2 * n].Y *= lazy[n].X; lazy[2 * n].Y %= MOD;
		lazy[2 * n].Y += lazy[n].Y; lazy[2 * n].Y %= MOD;
		lazy[2 * n + 1].X *= lazy[n].X; lazy[2 * n + 1].X %= MOD;
		lazy[2 * n + 1].Y *= lazy[n].X; lazy[2 * n + 1].Y %= MOD;
		lazy[2 * n + 1].Y += lazy[n].Y; lazy[2 * n + 1].Y %= MOD;
	}
	lazy[n].X = 1, lazy[n].Y = 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 세그트리, 레이지 프로퍼게이션
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 오버플로우
				  2. 곱연산을 레이지로 갱신할 때는, lazy의 초기값을 1로 설정하고, 곱연산 시행
*/////////////////////////////////////////////////////////////////////