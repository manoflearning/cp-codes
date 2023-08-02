#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

int n, par[101010], ind[101010], mnv[101010];
vt<int> chd[101010];
ll a[101010], mn[101010];

void init() {
    FOR(101010) {
        a[i] = par[i] = ind[i] = mnv[i] = 0;
        chd[i].clear();
        mn[i] = -1;
    }
}

void input() {
    cin >> n;
    FOR(i, 1, n + 1) cin >> a[i];
    FOR(i, 1, n + 1) {
        cin >> par[i];
        ind[par[i]]++;
        chd[par[i]].push_back(i);
    }
}

ll mnf(int v) {
    ll& ret = mn[v];
    if (chd[v].empty()) return ret = a[v];
    if (ret != -1) return ret;

    ret = INF;
    EACH(i, chd[v])
        ret = min(ret, mnf(i));
    ret = max(ret, a[v]);

    return ret;
}

void f(int v) {
    if (chd[v].empty()) return;

    mnv[v] = chd[v][0];
    EACH(i, chd[v]) {
        if (mnf(mnv[v]) > mnf(i)) mnv[v] = i;
    }
}

ll dfs(int v) {
    ll ret = a[v];
    if (mnv[par[v]] == v) ret = max(ret, dfs(par[v]));
    return ret;
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

    int tc; cin >> tc;

    FOR(t, tc) {
        cout << "Case #" << t + 1 << ": ";

        init();

        input();

        FOR(v, 1, n + 1) f(v);

        ll ans = 0;
        FOR(v, 1, n + 1) {
            if (ind[v]) continue;
            ans += dfs(v);
        }
        
        cout << ans << '\n';
    }

	return 0;
}

/*#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

int n, par[101010];
vt<int> chd[101010];
ll a[101010], dp[101010], mn[101010];

void init() {
    FOR(101010) {
        a[i] = par[i] = 0;
        chd[i].clear();
        dp[i] = mn[i] = -1;
    }
}

void input() {
    cin >> n;
    FOR(i, 1, n + 1) cin >> a[i];
    FOR(i, 1, n + 1) {
        cin >> par[i];
        chd[par[i]].push_back(i);
    }
}

ll mnf(int v) {
    ll& ret = mn[v];
    if (chd[v].empty()) return ret = a[v];
    if (ret != -1) return ret;

    ret = INF;
    EACH(i, chd[v])
        ret = min(ret, mnf(i));
    ret = max(ret, a[v]);

    return ret;
}

ll f(int v) {
    ll& ret = dp[v];
    if (chd[v].empty()) return ret = a[v];
    if (ret != -1) return ret;

    ret = a[v];

    int mnv = chd[v][0];
    EACH(i, chd[v]) {
        if (mnf(mnv) > mnf(i)) mnv = i;
    }

    ll lft = 0;
    EACH(i, chd[v]) {
        if (i == mnv) ret = max(ret, f(i));
        else lft += f(i);
    }

    return ret += lft;
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

    int tc; cin >> tc;

    FOR(t, tc) {
        cout << "Case #" << t + 1 << ": ";

        init();

        input();

        ll ans = 0;
        EACH(i, chd[0]) {
            ans += f(i);
        }

        cout << ans << '\n';
        if (t == 3) cout << f(3) << '\n';
    }

	return 0;
}*/