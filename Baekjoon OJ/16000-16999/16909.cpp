#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;
const int MAX = 1e6 + 5;

int flag;  // array size
struct mxSeg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}mxseg;

struct mnSeg {  // 1-indexed
	vector<ll> t;
    int x;

	void build(int n, int m) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, n + 1);

        x = m + 1;
		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return x;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}mnseg;

int n;
ll a[MAX];
int mxl[MAX], mxr[MAX], mnl[MAX], mnr[MAX];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    mxseg.build(MAX);

    for (int i = 1; i <= n; i++) {
        int l1 = mxseg.query(a[i], MAX), l2 = mxseg.query(1, a[i]);
        mxl[i] = l1 + 1, mnl[i] = l2 + 1;
        mxseg.modify(a[i], i);
    }

    mnseg.build(MAX, n); 

    for (int i = n; i >= 1; i--) {
        int r1 = mnseg.query(a[i] + 1, MAX), r2 = mnseg.query(1, a[i] - 1);
        mxr[i] = r1 - 1, mnr[i] = r2 - 1;
        mnseg.modify(a[i], i);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += a[i] * (mxr[i] - i + 1) * (i - mxl[i] + 1);
        ans -= a[i] * (mnr[i] - i + 1) * (i - mnl[i] + 1);
        //cout << a[i] << ' ' << mxl[i] << ' ' << mxr[i] << '\n';
    }

    cout << ans;

    return 0;
}