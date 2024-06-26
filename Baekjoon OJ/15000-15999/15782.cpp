#include <bits/stdc++.h>
using namespace std;
#define ll long long
int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] ^ t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) ^ query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] ^= lazy[n];
				lazy[n << 1 | 1] ^= lazy[n];
			}
			t[n] ^= lazy[n] * ((nr - nl + 1) & 1 ? 1 : 0);
			lazy[n] = 0;
		}
	}
}seg;

int n, m, in[101010], out[101010], w[101010], cnt;
vector<int> adj[101010];

void dfs(int v, int prv) {
    in[v] = ++cnt;
    for (auto& i : adj[v]) {
        if (i != prv) dfs(i, v);
    }
    out[v] = cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    dfs(1, -1);

    seg.build(n);

    for (int i = 1; i <= n; i++) {
        seg.modify(in[i], in[i], w[i]);
    }

    while (m--) {
        int op, x, y;
        cin >> op >> x;
        if (op == 2) cin >> y;

        if (op == 1) {
            cout << seg.query(in[x], out[x]) << '\n';
        }
        if (op == 2) {
            seg.modify(in[x], out[x], y);
        }
    }

	return 0;
}