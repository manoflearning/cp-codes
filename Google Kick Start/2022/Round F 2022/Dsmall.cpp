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

struct plr {
    int p, l, r;
};

int n, k, x, d;
int m;
vt<plr> a;
int vi[11], cnt = 0, ans = INF;

void init() {
    ans = INF;
}

void input() {
    cin >> n >> k >> x >> d;
    cin >> m;
    a.resize(m);
    EACH(i, a) cin >> i.p >> i.l >> i.r;
}

void cal() {
    int ret = INF;
    for (int i = 0; i + x <= d; i++) {
        int res = 0;
        EACH(j, a) {
            if (!vi[j.p]) continue;
            if (j.r <= i || i + x <= j.l) continue;
            res++;
        }
        ret = min(ret, res);
    }
    ans = min(ans, ret);
}

void bt(int idx) {
    if (idx == n + 1) {
        if (cnt == k) cal();
        return;
    }

    bt(idx + 1);

    vi[idx] = 1, cnt++;
    bt(idx + 1);
    vi[idx] = 0, cnt--;
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

        input();

        bt(1);

        cout << ans << '\n';
	}

	return 0;
}