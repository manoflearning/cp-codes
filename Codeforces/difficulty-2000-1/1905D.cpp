#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Node {
    ll cnt, val;
    Node operator+(const Node& rhs) const {
        Node ret;
        ret.cnt = cnt + rhs.cnt;
        ret.val = val + rhs.val;
        return ret;
    }
};

const Node e = { 0, 0 };

int flag;  // array size
struct Seg {  // 1-indexed
	vector<Node> t;
    vector<Node> lazy;
    vector<bool> lazyCheck;
	void build(int n) {
        t.clear();
        lazy.clear();
        lazyCheck.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
        lazyCheck.resize(2 * flag);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, Node v, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] = v;
            lazyCheck[n] = 1;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, v, n << 1, nl, mid);
		modify(l, r, v, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return e;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazyCheck[n]) {
			if (n < flag) {
				lazy[n << 1].cnt = lazy[n].cnt;
                lazy[n << 1].val = lazy[n].val;
                lazyCheck[n << 1] = 1;
				lazy[n << 1 | 1].cnt = lazy[n].cnt;
                lazy[n << 1 | 1].val = lazy[n].val;
                lazyCheck[n << 1 | 1] = 1;
			}
			t[n] = lazy[n];
            lazyCheck[n] = 0;
			lazy[n] = e;
		}
	}
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> p(n);
        for (auto& i : p) cin >> i;

        int idx0 = -1;
        for (int i = 0; i < sz(p); i++) {
            if (p[i] == 0) { idx0 = i; break; }
        }

        seg.build(n);
        seg.modify(n, n, { 1, n });

        ll ans = seg.query(0, n).val;
        for (int i = (idx0 + 1) % n; i != idx0; i = (i + 1) % n) {
            int x = p[i];

            ll cnt = seg.query(x + 1, n).cnt;

            seg.modify(x + 1, n, { 0, 0 });
            seg.modify(x, x, { cnt, cnt * x });

            seg.modify(n, n, { 1, n });
            ans = max(ans, seg.query(0, n).val);
        }

        cout << ans << '\n';
    }
}