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

int n, par[202020];
vt<int> chd[202020];
pll lr[202020];
ll dp[202020], dp2[202020];

void init() {
    FOR(i, n + 1) {
        par[i] = dp[i] = dp2[i] = 0;
        chd[i].clear();
        lr[i] = { 0, 0 };
    }
    n = 0;
}

ll f2(int v) { // dp2[v] = 노드 v를 최소한으로 지났을 때 가능한 a[v]의 최댓값.
    ll& ret = dp2[v];
    if (chd[v].empty()) ret = lr[v].sc;
    
    EACH(i, chd[v]) {
        ret += f2(i);
    }
    if (ret < lr[v].fr || lr[v].sc < ret) ret = lr[v].sc;
    return ret;
}

ll f(int v) { // dp[v] = 노드 v를 지나는 최소 횟수
    ll& ret = dp[v];
    if (chd[v].empty()) return ret = 1;

    ll sum = 0;
    EACH(i, chd[v]) {
        ret += f(i);
        sum += dp2[i];
    }
    if (sum < lr[v].fr) ret++;
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

    while (tc--) {
        cin >> n;
        FOR(i, 2, n + 1) {
            cin >> par[i];
            chd[par[i]].push_back(i);
        }
        FOR(i, 1, n + 1) {
            cin >> lr[i].fr >> lr[i].sc;
        }

        f2(1);
        cout << f(1) << '\n';

        init();
    }

	return 0;
}