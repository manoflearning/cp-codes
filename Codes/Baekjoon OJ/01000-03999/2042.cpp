#include <iostream>
using namespace std;
#define ll long long

const int MAXN = 1e6;  // limit for array size

struct Seg {
	int N;  // array size
	ll t[2 * MAXN];

	void build() {
		//cin >> N;
		for (int i = 0; i < N; i++) cin >> t[N + i];
		for (int i = N - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, int value) {  // set value at position p
		for (t[p += N] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = 0;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int M, K;
	cin >> seg.N >> M >> K;

	seg.build();

	for (int i = 0; i < M + K; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 1) seg.modify(b - 1, c);
		else cout << seg.query(b - 1, c) << '\n';
	}

	return 0;
}