#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Tree {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> p(n);
        for (auto &i : p) cin >> i;

        // vector<int> inv(n), pinv(n);

        // Tree seg(n + 1);
        // for (int i = n - 1; i >= 0; i--) {
        //     inv[i] = seg.query(1, p[i] - 1);
        //     seg.update(p[i], 1);
        // }

        // for (int i = 0; i < n; i++) {
        //     pinv[i] = inv[i] + (i > 0 ? pinv[i - 1] : 0);
        // }

        // for (int i = 1; i <= n; i++) seg.update(i, 0);

        ll ans = 0;

        Tree seg_l(n + 1);
        for (int b = 1; b < n; b++) {
            seg_l.update(p[b - 1], 1);

            Tree seg_r(n + 1);
            for (int c = n - 2; c > b; c--) {
                seg_r.update(p[c + 1], 1);
                ans += seg_l.query(1, p[c]) * seg_r.query(1, p[b]);
            }
        }

        cout << ans << '\n';
    }
}
