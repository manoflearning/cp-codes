#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;  // array size
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) t[i] = 1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int p, ll value) {  // add value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    ll kth(ll k, int n = 1) { // find the kth smallest number (1-indexed)
        assert(t[n] >= k);
        if (flag <= n) return n - flag + 1;
        if (k <= t[n << 1]) return kth(k, n << 1);
        else return kth(k - t[n << 1], n << 1 | 1);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int n, m;
int lcnt, rcnt;
bool del_init = 1;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;

    seg.build(n);

    lcnt = n / 2;
    rcnt = n / 2;

    while (m--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            if ((n & 1) && del_init) {
                if (x <= (n + 1) / 2) lcnt++;
                else rcnt++;
                del_init = 0;
            }

            if (seg.query(1, x) <= lcnt) lcnt--;
            else rcnt--;

            seg.add(x, 0);
        }
        if (op == 2) {
            assert(!(x <= lcnt && n - x + 1 <= rcnt));

            if ((n & 1) && del_init) {
                cout << x << '\n';
            }
            else if (x <= lcnt) {
                cout << seg.kth(x) << '\n';
            }
            else if (n - x + 1 <= rcnt) {
                cout << seg.kth((lcnt + rcnt) - (n - x)) << '\n';
            }
            else cout << 0 << '\n';
        }
    }
}
