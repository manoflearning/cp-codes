#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define pii pair<int, int>

const int MAX = 1e5;

struct Seg {
	int N, t[2 * MAX];

	void modify(int p) {
		for (t[p += N] = 1; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	int query(int l, int r) {
		int ret = 0;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

struct ijk {
	int i, j, k, idx;
};

priority_queue<pii> pq;
int M;
ijk Q[MAX + 5];
int ans[MAX + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> seg.N;
	for (int i = 0; i < seg.N; i++) {
		int A; cin >> A;
		pq.push({ A, i });
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> Q[i].i >> Q[i].j >> Q[i].k;
		Q[i].idx = i;
	}

	sort(Q, Q + M, [](ijk& a, ijk& b) {
		return a.k > b.k;
		});

	for (int i = 0; i < M; i++) {
		while (!pq.empty() && pq.top().first > Q[i].k) {
			seg.modify(pq.top().second);
			pq.pop();
		}
		ans[Q[i].idx] = seg.query(Q[i].i - 1, Q[i].j);
	}
	
	for (int i = 0; i < M; i++) cout << ans[i] << '\n';

	return 0;
}