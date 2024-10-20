#define _USE_MATH_DEFINES
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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct xidx {
    ll x, idx;
    bool operator<(const xidx& rhs) const {
        if (x != rhs.x) return x > rhs.x;
        return idx > rhs.idx;
    }
};

ll m, t, n, ans[10101];
priority_queue<xidx> LL, RR;

void cal(priority_queue<xidx>& a, priority_queue<xidx>& b, ll& tnow) {
    //cout << tnow << ' ' << (sz(a) ? a.top().x : -1) << ' ' << (sz(b) ? b.top().x : -1) << '\n';
    int cnt = 0;
    while (cnt < m && sz(a) && tnow >= a.top().x) {
        cnt++, ans[a.top().idx] = tnow + t;
        a.pop();
    }
    if (cnt > 0) tnow += t;

    if (cnt == 0) {
        if (a.empty() || (sz(a) && sz(b) && a.top().x > b.top().x)) tnow = max(tnow, b.top().x) + t;
        else if (b.empty() || (sz(a) && sz(b) && a.top().x <= b.top().x)) {
            int prv = -1;
            while ((prv == -1 || prv == a.top().x) && cnt < m) {
                cnt++, ans[a.top().idx] = a.top().x + t;
                tnow = a.top().x + t;
                prv = a.top().x;
                a.pop();
            }
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> m >> t >> n;
    FOR(n) {
        int x; string s;
        cin >> x >> s;
        if (s == "left") LL.push({ x, i });
        else RR.push({ x, i });
    }

    ll tnow = 0, dirnow = 0, cnt = 0;
    while (sz(LL) || sz(RR)) {
        if (dirnow == 0) cal(LL, RR, tnow);
        else if (dirnow == 1) cal(RR, LL, tnow);
        dirnow = !dirnow;
        assert(cnt++ < 3 * n);
    }

    FOR(n) cout << ans[i] << '\n';

	return 0;
}