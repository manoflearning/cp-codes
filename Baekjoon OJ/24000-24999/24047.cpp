//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505050;  // limit for array size
const int INF = 1e9 + 7;

struct Seg {  // 0-indexed
	int n;  // array size
	int t[2 * MAXN];
	void build(int N) {
		n = N;
        for (int i = 0; i < 2 * MAXN; i++) t[i] = INF;
	}
	void modify(int p, int value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int ret = INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, t[l++]);
			if (r & 1) ret = min(ret, t[--r]);
		}
		return ret;
	}
}seg;

int n, k;
int a[505050];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n + 1; i < 505050; i++) a[i] = INF;

    seg.build(n + 1);
    for (int i = 1; i < n; i++)
        if (a[i] > a[i + 1]) seg.modify(i, i);

    int cnt = 0;
    for (int last = n; last >= 2; last--) {
        for (int lb = 1; lb < last; ) {
            int idx = seg.query(lb, last);
            if (idx >= last) break;

            cnt++;
            swap(a[idx], a[idx + 1]);
            seg.modify(idx, INF);
            if (seg.t[idx + n] == INF && a[idx - 1] > a[idx]) seg.modify(idx - 1, idx - 1);
            if (seg.t[idx + 2 + n] == INF && a[idx + 1] > a[idx + 2]) seg.modify(idx + 1, idx + 1);

            if (cnt == k) break;
            
            lb = idx + 1;
        }

        if (cnt == k) break;
    }

    if (cnt < k) {
        cout << -1;
        return 0;
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
}