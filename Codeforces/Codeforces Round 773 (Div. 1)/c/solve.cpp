#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

inline char gc() { // like getchar()
	static char buf[1 << 16];
	static size_t bc, be;
	if (bc >= be) {
		buf[0] = 0, bc = 0;
		be = fread(buf, 1, sizeof(buf), stdin);
	}
	return buf[bc++]; // returns 0 on EOF
}

int readInt() {
	int a, c;
	while ((a = gc()) < 40);
	if (a == '-') return -readInt();
	while ((c = gc()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}

constexpr int INF = 1e9 + 7;
struct seg_tree_lz {
    int flag;
    vector<int> t;
    vector<bool> lz;
    void init(int n) {
        // goal: allocate tree and clear lazy tags (all zeros).
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, 0);
        lz.assign(2 * flag, 0);
        for (int i = flag; i < flag + n; i++) t[i] = 1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void del(int l, int r) { del(l, r, 1, 1, flag); }
    void del(int l, int r, int v, int nl, int nr) {
        // goal: add val to all indices in [l, r].
        push(v, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lz[v] = 1;
            push(v, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        del(l, r, v << 1, nl, mid);
        del(l, r, v << 1 | 1, mid + 1, nr);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
    int query(int l, int r) { return query(l, r, 1, 1, flag); }
    int query(int l, int r, int v, int nl, int nr) {
        // result: sum on [l, r].
        push(v, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return query(l, r, v << 1, nl, mid) + query(l, r, v << 1 | 1, mid + 1, nr);
    }
    void push(int v, int nl, int nr) {
        // goal: propagate lazy value to children.
        if (lz[v] == 0) return;
        if (v < flag) {
            lz[v << 1] = 1;
            lz[v << 1 | 1] = 1;
        }
        t[v] = lz[v] = 0;
    }

    int kth_f(int k) { return kth_f(k, 1, 1, flag); }
    int kth_b(int k) { return kth_b(k, 1, 1, flag); }
    int kth_f(int k, int v, int nl, int nr) {
        push(v, nl, nr);
        if (nl == nr) {
            if (k == t[v]) return nl;
            else {
                assert(nl == flag);
                return flag + 1;
            }
        }

        int mid = (nl + nr) >> 1;
        push(v << 1, nl, mid);
        if (k <= t[v << 1]) return kth_f(k, v << 1, nl, mid);
        else return kth_f(k - t[v << 1], v << 1 | 1, mid + 1, nr);
    }
    int kth_b(int k, int v, int nl, int nr) {
        push(v, nl, nr);
        if (nl == nr) {
            if (k == t[v]) return nl;
            else {
                // cout << nl << ' ' << k << endl;
                assert(nl == 1);
                return 0;
            }
        }

        int mid = (nl + nr) >> 1;
        push(v << 1 | 1, mid + 1, nr);
        if (k <= t[v << 1 | 1]) return kth_b(k, v << 1 | 1, mid + 1, nr);
        else return kth_b(k - t[v << 1 | 1], v << 1, nl, mid);
    }
};

struct Tree {
	typedef int T;
	static constexpr T unit = INT_MAX;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
        pos += n;
		for (s[pos] = min(s[pos], val); pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n = readInt(), q = readInt();

    seg_tree_lz seg0;
    seg0.init(n);
    Tree seg1{n + 1};

    while (q--) {
        int op = readInt();

        if (op == 0) {
            int l = readInt(), r = readInt(), x = readInt();

            if (x == 0) seg0.del(l, r);
            else seg1.update(l, r);
        } else {
            int j = readInt();
            if (seg0.query(j, j) == 0) {
                cout << "NO\n";
            } else {
                // for (int i = 1; i <= n; i++) cout << seg0.query(i, i) << ' ';
                // cout << '\n';

                const int k_f = seg0.query(1, j) + 1;
                const int k_b = seg0.query(j, n) + 1;

                // cout << k_b << '\n';
                const int s = seg0.kth_b(k_b) + 1;
                const int e = min(n, seg0.kth_f(k_f) - 1);

                // cout << j << ' ';
                // cout << k_f << ' ' << k_b << ' ';
                // cout << s << ' ' << e << '\n';

                bool yes = seg1.query(s, j + 1) <= e;
                cout << (yes ? "YES" : "N/A") << '\n';
            }
        }
    }
}
