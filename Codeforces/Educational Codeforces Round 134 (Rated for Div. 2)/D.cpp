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

struct ab {
    vt<int> a, b;
};

int n;
vt<ab> sarr(1);
ll ans;

void init() {
    sarr.clear();
    sarr.resize(1);
    ans = 0;
}

void input() {
    cin >> n;
    sarr[0].a.resize(n);
    sarr[0].b.resize(n);
    EACH(i, sarr[0].a) cin >> i;
    EACH(i, sarr[0].b) cin >> i;
}

void f(int idx) {
    if (idx == -1) return;
    
    int add = 1;
    EACH(arr, sarr) {
        int cnta = 0, cntb = 0;
        EACH(i, arr.a)
            if (i & (1 << idx)) cnta++;
        EACH(i, arr.b)
            if (i & (1 << idx)) cntb++;
        //cout << idx << ' ' << cnta << ' ' << cntb << ' ' << sz(arr.a) << '\n';
        if (cnta + cntb != sz(arr.a)) { add = 0; break; }
    }

    if (!add) { f(idx - 1); return; }

    ans += (1 << idx);

    vt<ab> nsarr;
    EACH(arr, sarr) {
        vt<int> nla, nlb, nra, nrb;

        EACH(i, arr.a) {
            if (i & (1 << idx)) nla.push_back(i);
            else nra.push_back(i);
        }
        EACH(i, arr.b) {
            if (i & (1 << idx)) nrb.push_back(i);
            else nlb.push_back(i);
        }

        if (sz(nla)) nsarr.push_back({ nla, nlb });
        if (sz(nra)) nsarr.push_back({ nra, nrb });
    }

    sarr = nsarr;

    f(idx - 1);
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
        init();

		input();

        f(29);

        cout << ans << '\n';
	}

	return 0;
}