#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

int flag;
struct Seg {
    vector<ll> t, lazy;

    void build(int n, const vector<int>& w, const vector<int>& in, const vector<int>& out) {
        for (flag = 1; flag < 2 * n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
        
        for (int i = 1; i <= n; i++) {
            t[flag + in[i] - 1] = w[i];
            t[flag + out[i] - 1] = w[i];
        }
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n]) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n] += (nr - nl + 1) * lazy[n];
            lazy[n] = 0;
        }
    }
    void modify(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);

        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            propagate(n, nl, nr);
            return;
        }

        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);

        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) {
            propagate(n, nl, nr);
            return t[n];
        }

        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, q, num;
vector<int> w, in, out;
vector<int> chd[505050];

void input() {
    cin >> n >> q;

    w.resize(n + 1);
    in.resize(n << 1 | 1);
    out.resize(n << 1 | 1);

    cin >> w[1];
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> w[i] >> p;
        chd[p].push_back(i);
    }
}

void dfs(int v) {
    in[v] = ++num;
    for (auto& i : chd[v]) dfs(i);
    out[v] = ++num;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    dfs(1);

    seg.build(n, w, in, out);

    while (q--) {
        char op;
        int x, y;
        cin >> op >> x;

        if (op == 'p') {
            cin >> y;
            seg.modify(in[x] + 1, out[x] - 1, y);
        }
        else {
            cout << seg.query(in[x], in[x]) << '\n';
        }
    }

	return 0;
}