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

struct Block {
    ll h;
    int idx;
};

int n;
ll a[303030], dp[303030][3];
vt<Block> block(1, { 0, 0 });

void init() {
    FOR(303030) FOR(j, 3) dp[i][j] = -INF - 1;
}

void input() {
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        if (a[i]) block.push_back({ a[i], i });
    }
}

ll f(int x, int dir) {
    ll& ret = dp[x][dir];
    if (ret != -INF - 1) return ret;
    if (x == 0) return ret = 0;

    ll h = block[x].h, ph = block[x - 1].h;
    int idx = block[x].idx, pidx = block[x - 1].idx;

    if (dir == 0) {
        ll lb = idx - h;

        if (lb < 1) ret = -INF;
        else if (lb < pidx) ret = -INF;
        else {
            if (lb == pidx) ret = f(x - 1, 0) + h;
            else if (pidx < lb && lb <= pidx + ph) ret = max(f(x - 1, 0), f(x - 1, 1)) + h;
            else if (pidx + ph < lb) {
                ret = max({ f(x - 1, 0), f(x - 1, 1), f(x - 1, 2) }) + h;
            }
        }
    }
    else if (dir == 1) {
        ret = max({ f(x - 1, 0), f(x - 1, 1) }) + 1;
        
        if (pidx + ph < idx) 
            ret = max(ret, f(x - 1, 2) + 1);
    }
    else if (dir == 2) {
        ret = max({ f(x - 1, 0), f(x - 1, 1) }) + h;

        if (pidx + ph <= idx)
            ret = max(ret, f(x - 1, 2) + h);
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	input();

    ll ans = 0;
    ans = max(ans, f(sz(block) - 1, 0));
    ans = max(ans, f(sz(block) - 1, 1));
    if (block.back().idx + block.back().h <= n) 
        ans = max(ans, f(sz(block) - 1, 2));

    cout << n - ans;

	return 0;
}