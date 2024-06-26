// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy, cnt;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
        cnt.resize(2 * flag);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] = (r - nr) * value;
            cnt[n] = value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (cnt[n] != 0) {
            int len = nr - nl + 1;
			if (n < flag) {
				lazy[n << 1] = lazy[n] + cnt[n] * len / 2;
				lazy[n << 1 | 1] = lazy[n];

                cnt[n << 1] = cnt[n];
                cnt[n << 1 | 1] = cnt[n];
			}
			t[n] = (2 * lazy[n] + cnt[n] * (len - 1)) * len / 2;
			lazy[n] = cnt[n] = 0;
		}
	}
}seg;

int n, m, q;
map<int, ll> mp;
int X[303030];
ll V[303030];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) cin >> X[i];
    for (int i = 1; i <= m; i++) cin >> V[i];
    
    for (int i = 1; i <= m; i++) mp[X[i]] = V[i];

    seg.build(n);
    auto it1 = mp.begin(), it2 = mp.begin();
    it2++;
    while (it2 != mp.end()) {
        seg.modify(it1->fr + 1, it2->fr, it1->sc);
        it1++, it2++;
    }

    // for (int i = 1; i <= n; i++)
        // cout << seg.query(i, i) << '\n';

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x; ll v;
            cin >> x >> v;

            mp[x] = v;
            auto itm = mp.find(x);
            auto itl = mp.find(x), itr = mp.find(x);
            itl--, itr++;
            seg.modify(itl->fr + 1, itm->fr, itl->sc);
            seg.modify(itm->fr + 1, itr->fr, itm->sc);
        }
        if (op == 2) {
            int l, r;
            cin >> l >> r;
            cout << seg.query(l, r) << '\n';
        }
    }
}