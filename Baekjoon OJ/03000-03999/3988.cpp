#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, k;
vector<ll> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n + 1);
    a[0] = -1e9;
    for (int i = 1; i <= n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    seg.build(n);

    for (int i = 2; i <= n; i++) {
        seg.modify(i, a[i] - a[i - 1]);
    }

    ll ans = INF;
    int len = n - k;
    for (int i = len; i <= n; i++) {
        ans = min(ans, a[i] - a[i - len + 1] + seg.query(i - len + 2, i));
    }

    cout << ans;

    return 0;
}