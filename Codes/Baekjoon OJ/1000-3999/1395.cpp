#include <iostream>
#include <vector>
using namespace std;

int flag;
vector<int> sgtr;
vector<bool> lazy;

int cnt(int L, int R, int n, int nL, int nR);
void update(int L, int R, int n, int nL, int nR);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	for (flag = 1; flag < n; flag *= 2);
	sgtr.resize(2 * flag);
	lazy.resize(2 * flag);

	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 0) update(b, c, 1, 1, flag);
		else cout << cnt(b, c, 1, 1, flag) << '\n';
	}

	return 0;
}

int cnt(int L, int R, int n, int nL, int nR) {
	if (lazy[n]) {
		sgtr[n] = (nR - nL + 1) - sgtr[n];
		if (n < flag) {
			if (lazy[2 * n]) lazy[2 * n] = false;
			else lazy[2 * n] = true;
			if (lazy[2 * n + 1]) lazy[2 * n + 1] = false;
			else lazy[2 * n + 1] = true;
		}
		lazy[n] = false;
	}

	if (R < nL || nR < L) return 0;
	if (L <= nL && nR <= R) return sgtr[n];

	int mid = (nL + nR) / 2;
	return cnt(L, R, 2 * n, nL, mid) + cnt(L, R, 2 * n + 1, mid + 1, nR);
}
void update(int L, int R, int n, int nL, int nR) {
	if (lazy[n]) {
		sgtr[n] = (nR - nL + 1) - sgtr[n];
		if (n < flag) {
			if (lazy[2 * n]) lazy[2 * n] = false;
			else lazy[2 * n] = true;
			if (lazy[2 * n + 1]) lazy[2 * n + 1] = false;
			else lazy[2 * n + 1] = true;
		}
		lazy[n] = false;
	}

	if (R < nL || nR < L) return;
	if (L <= nL && nR <= R) {
		sgtr[n] = (nR - nL + 1) - sgtr[n];
		if (n < flag) {
			if (lazy[2 * n]) lazy[2 * n] = false;
			else lazy[2 * n] = true;
			if (lazy[2 * n + 1]) lazy[2 * n + 1] = false;
			else lazy[2 * n + 1] = true;
		}
		return;
	}

	int mid = (nL + nR) / 2;
	update(L, R, 2 * n, nL, mid);
	update(L, R, 2 * n + 1, mid + 1, nR);

	sgtr[n] = sgtr[2 * n] + sgtr[2 * n + 1];
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 세그트리 w 레이지 프로퍼게이션
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////