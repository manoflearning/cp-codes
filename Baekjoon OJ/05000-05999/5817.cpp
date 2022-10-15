#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int flag;  // array size
struct mxSeg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}mxidx;

struct mnSeg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}mnidx;

int n, m, a[202020], loc[202020];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    mxidx.build(n);
    mnidx.build(n);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = x;
        loc[x] = i;
        mxidx.modify(x, i);
        mnidx.modify(x, i);
    }

    for (int i = 0; i < m; i++) {
        int op, u, v;
        cin >> op >> u >> v;

        if (op == 1) {
            mxidx.modify(a[v], u);
            mxidx.modify(a[u], v);
            mnidx.modify(a[v], u);
            mnidx.modify(a[u], v);
            swap(loc[a[u]], loc[a[v]]);
            swap(a[u], a[v]);
        }
        else {
            int l = mnidx.query(u, v), r = mxidx.query(u, v);
            if (r - l == v - u) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}