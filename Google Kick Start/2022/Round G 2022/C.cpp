#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const ll INF = 1e12;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int flag;  // array size
struct Seg {  // 1-indexed
	struct Node {
        ll mn, sum;
        Node operator+(const Node& rhs) {
            return { min(mn, sum + rhs.mn), sum + rhs.sum };
        }
    };
    
    vector<Node> t;

	void build(int n, const vector<ll>& a) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, { INF, 0 });

		for (int i = flag; i < 2 * flag; i++) {
            if (i < flag + n) t[i].mn = t[i].sum = a[i - flag + 1];
            else t[i].mn = t[i].sum = -INF;
        }
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = { value, value }; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
	}
    int query(ll sum, int n = 1, int nl = 1, int nr = flag) {
        if (nl == nr) return nl;
        
        int mid = (nl + nr) >> 1;
        if (sum + t[n << 1].mn < 0) return query(sum, n << 1, nl, mid);
        else return query(sum + t[n << 1].sum, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n;
vector<ll> a, psum, psum2;

void init() {
    seg.t.clear();
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cout << "Case #" << tt << ": ";

        init();

        cin >> n;
        a.resize(n + 1);
        FOR(n) cin >> a[i + 1];

        n++;
        a.push_back(-INF);

        seg.build(n, a);

        psum.resize(n);
        psum2.resize(n);
        for (int i = 1; i < n; i++) {
            psum[i] = a[i] + psum[i - 1];
            psum2[i] = a[i] + psum2[i - 1] + psum[i - 1];
        }
        
        ll ans = 0;
        for (int i = 1; i < n; i++) {
            if (i > 1) seg.modify(i - 1, 0);

            int idx = seg.query(0) - 1;

            if (idx < i) continue;
            //cout << i << ' ' << idx << '\n';
            ans += psum2[idx] - psum2[i - 1] - (idx - i + 1) * psum[i - 1];
        }

        cout << ans << '\n';
	}

	return 0;
}