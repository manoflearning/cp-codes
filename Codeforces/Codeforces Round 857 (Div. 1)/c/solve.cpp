#pragma GCC optimize ("Ofast, unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
        pos += n;
		for (s[pos] = max(s[pos], val); pos >>= 1;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b >>= 1, e >>= 1) {
			if (b & 1) ra = f(ra, s[b++]);
			if (e & 1) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<vector<int>> a(n);
        for (auto &i : a) {
            int k; cin >> k;
            while (k--) {
                int x; cin >> x;
                if (i.empty() || i.back() < x) {
                    i.push_back(x);
                }
            }
        }

        vector<int> cc(1, -1);
        for (auto &i : a) {
            for (auto &j : i) cc.push_back(j);
        }
        sort(all(cc));
        cc.erase(unique(all(cc)), cc.end());
        for (auto &i : a) {
            for (auto &j : i) {
                j = lower_bound(all(cc), j) - cc.begin();
            }
        }

        vector<int> ord(n);
        iota(all(ord), 0);

        sort(all(ord), [&](int i, int j) {
            return a[i].back() < a[j].back();
        });
    
        Tree seg{sz(cc)};

        // base case
        seg.update(0, 0);

        // inductive step
        for (int i : ord) {
            int res = 0;
            for (int j = 0; j < sz(a[i]); j++) {
                const int prv = j == 0 ? 0 : a[i][j - 1];
                const int now = a[i][j];
                res = max(res, seg.query(prv, now) + sz(a[i]) - j);
            }
            seg.update(a[i].back(), res);
        }

        cout << seg.query(0, sz(cc)) << '\n';
    }
}
