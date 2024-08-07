#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;  // array size
struct Seg {  // 1-indexed
    vector<int> du;
	vector<vector<int>> t;
    vector<int> lazy;

    void sum(vector<int>& a, vector<int>& u, vector<int>& v) {
        for (int i = 0; i < 10; i++) {
            a[i] = u[i] + v[i];
        }
    }
	void build(int n, const string& s) {
		for (flag = 1; flag < n; flag <<= 1);

        du.resize(10);

		t.resize(2 * flag, du);
		lazy.resize(2 * flag);

		for (int i = flag; i < flag + n; i++) t[i][s[i - flag] - '0'] = 1;
		for (int i = flag - 1; i >= 1; i--) sum(t[i], t[i << 1], t[i << 1 | 1]);
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

		sum(t[n], t[n << 1], t[n << 1 | 1]);
	}
	vector<int> query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);

		if (r < nl || nr < l) return du;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
        
        vector<int> ret(10), u = query(l, r, n << 1, nl, mid), v = query(l, r, n << 1 | 1, mid + 1, nr);
        for (int i = 0; i < 10; i++) {
            ret[i] = u[i] + v[i];
        }
		return ret;
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}

            vector<int> tmp(10);
            for (int i = 0; i < 10; i++) {
                tmp[(i + lazy[n]) % 10] = t[n][i];
            }
			t[n] = tmp;
			lazy[n] = 0;
		}
	}
}seg;

int n, m;
string s;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    cin >> s;

    seg.build(n, s);

    while (m--) {
        int l, r;
        cin >> l >> r;

        vector<int> res = seg.query(l, r);
        
        ll ans = 0;
        for (int i = 0; i < 10; i++)
            ans += res[i] * i;

        cout << ans << '\n';

        seg.modify(l, r, 1);
    }

    return 0;
}