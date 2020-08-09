#include <iostream>
#include <vector>
using namespace std;

int flag;
vector<int> sgtr, lazy;

void update(int L, int R, int n, int nL, int nR, int k);
int XOR(int L, int R, int n, int nL, int nR);
void propagate(int n, int nL, int nR);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int N; cin >> N;

	for (flag = 1; flag < N; flag *= 2);
	sgtr.resize(2 * flag);
	lazy.resize(2 * flag);

	for (int i = flag; i < flag + N; i++)
		cin >> sgtr[i];

	for (int i = flag - 1; i >= 1; i--)
		sgtr[i] = sgtr[2 * i] ^ sgtr[2 * i + 1];

	int Q; cin >> Q;
	while (Q--) {
		int q, L, R;
		cin >> q >> L >> R;
		L++, R++;

		if (q == 1) {
			int k; cin >> k;
			update(L, R, 1, 1, flag, k);
		}
		else cout << XOR(L, R, 1, 1, flag) << '\n';
	}

	return 0;
}

void update(int L, int R, int n, int nL, int nR, int k) {
	propagate(n, nL, nR);

	if (R < nL || nR < L) return;
	if (L <= nL && nR <= R) {
		lazy[n] ^= k;
		propagate(n, nL, nR);
		return;
	}

	int mid = (nL + nR) / 2;
	update(L, R, 2 * n, nL, mid, k);
	update(L, R, 2 * n + 1, mid + 1, nR, k);

	sgtr[n] = sgtr[2 * n] ^ sgtr[2 * n + 1];
}

int XOR(int L, int R, int n, int nL, int nR) {
	propagate(n, nL, nR);

	if (R < nL || nR < L) return 0;
	if (L <= nL && nR <= R) return sgtr[n];

	int mid = (nL + nR) / 2;
	return XOR(L, R, 2 * n, nL, mid) ^ XOR(L, R, 2 * n + 1, mid + 1, nR);
}

void propagate(int n, int nL, int nR) {
	if (lazy[n] != 0) {
		if (n < flag) {
			lazy[2 * n] ^= lazy[n];
			lazy[2 * n + 1] ^= lazy[n];
		}
		if ((nR - nL + 1) % 2 == 1) sgtr[n] ^= lazy[n];
		lazy[n] = 0;
	}
}