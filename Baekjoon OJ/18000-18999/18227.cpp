#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 202020;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
	}
	void add(int p) {  // set value at position p
		for (t[p += flag - 1]++; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int n, root;
vector<int> adj[MAXN];
int in[MAXN], out[MAXN], pv = 0;
int dep[MAXN];

void input() {
    cin >> n >> root;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    in[v] = ++pv;
	for (auto& i : adj[v]) {
		if (i != prv) {
            dep[i] = dep[v] + 1;
            dfs(i, v);
        }
	}
    out[v] = pv;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dep[root] = 1;
    dfs(root, -1);

    seg.build(n);

    int q; cin >> q;
    while (q--) {
        int op, v;
        cin >> op >> v;

        if (op == 1) seg.add(in[v]);
        if (op == 2) cout << dep[v] * seg.query(in[v], out[v]) << '\n';
    }
}
