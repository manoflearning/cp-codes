//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
struct MinSeg {  // 1-indexed
	vector<pii> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, { INF, INF });
	}
	void modify(int p, int value) {  // set value at position p
        t[p + flag - 1] = { value, p };
		for (p += flag - 1; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	pii query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return { INF, INF };
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}mnasg, mnbsg;
struct MaxSeg {  // 1-indexed
	vector<pii> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, { -INF, -INF });
	}
	void modify(int p, int value) {  // set value at position p
        t[p + flag - 1] = { value, p };
		for (p += flag - 1; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	pii query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return { -INF, -INF };
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}mxasg, mxbsg;

int n, a[252525], b[252525];
map<int, vector<int>> mp;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}

void buildSeg() {
    mnasg.build(n);
    mnbsg.build(n);
    for (int i = 1; i <= n; i++) {
        mnasg.modify(i, a[i]);
        mnbsg.modify(i, b[i]);
    }
    mxasg.build(n);
    mxbsg.build(n);
    for (int i = 1; i <= n; i++) {
        mxasg.modify(i, a[i]);
        mxbsg.modify(i, b[i]);
    }
}

ll ans = 0;

void dnc(ll l, ll r, int op) {
    if (l > r) return;

    pii mna = mnasg.query(l, r), mxa = mxasg.query(l, r);
    pii mnb = mnbsg.query(l, r), mxb = mxbsg.query(l, r);

    if (mna.fr == mnb.fr && mxa.fr == mxb.fr) {
        // ll sa = min({ mna.sc, mxa.sc });
        // ll ea = max({ mna.sc, mxa.sc });
        // ll sb = min({ mnb.sc, mxb.sc });
        // ll eb = max({ mnb.sc, mxb.sc });

        ll s = min({ mna.sc, mxa.sc, mnb.sc, mxb.sc });
        ll e = max({ mna.sc, mxa.sc, mnb.sc, mxb.sc });
        ans += op * (s - l + 1) * (r - e + 1);

        dnc(l, e - 1, op);
        dnc(s + 1, r, op);
        dnc(s + 1, e - 1, -op);
    }
    else if (mna.fr != mnb.fr) {
        if (mna.fr > mnb.fr) swap(mna, mnb);
        vector<int> mnas = mp[mna.fr];
        int prv = l;
        for (auto& p : mnas) {
            dnc(prv, p - 1, op);
            prv = p + 1;
        }
        dnc(prv, r, op);

        // int p = (mna.fr < mnb.fr ? mna.sc : mnb.sc);        
        // dnc(l, p - 1, op);
        // dnc(p + 1, r, op);
    }
    else if (mxa.fr != mxb.fr) {
        if (mxa.fr < mxb.fr) swap(mxa, mxb);
        vector<int> mxas = mp[mxa.fr];
        int prv = l;
        for (auto& p : mxas) {
            dnc(prv, p - 1, op);
            prv = p + 1;
        }
        dnc(prv, r, op);

        // int p = (mxa.fr > mxb.fr ? mxa.sc : mxb.sc);
        // dnc(l, p - 1, op);
        // dnc(p + 1, r, op);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildSeg();

    for (int i = 1; i <= n; i++)
        mp[a[i]].push_back(i);

    dnc(1, n, 1);

    cout << ans;
}