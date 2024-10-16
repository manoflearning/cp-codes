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

const int MAX = 1010101;

int n, k;
vt<int> a;
int dp[MAX][9];
vt<int> sw[8];

void init() {
    FOR(MAX) FOR(j, 9) dp[i][j] = -1;
}

void input() {
    cin >> n >> k;
    a.resize(n);
    EACH(i, a) cin >> i;

    FOR(k) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x;
            sw[i].push_back(x - 1);
        }
    }
}

int Hash(const vt<int>& a) {
    int bit = 1, ret = 0;
    EACH(i, a) {
        ret += bit * i;
        bit *= 5;
    }
    return ret;
}

vt<int> rHash(int bit) {
    vt<int> ret;
    FOR(n) {
        ret.push_back(bit % 5);
        bit /= 5;
    }
    return ret;
}

int f(int bit, int idx) {
    int& ret = dp[bit][idx];
    vt<int> res = rHash(bit);
    if (ret != -1) return ret;
    if (idx == k) {
        int ans = 1;
        FOR(sz(res) - 1) {
            if (res[i] ^ res[i + 1]) ans = 0;
        }
        
        if (ans) return ret = 0;
        else return ret = INF;
    }

    ret = INF;
    FOR(5) {
        vt<int> nres = res;
        EACH(j, sw[idx]) {
            nres[j] += (idx + 1) * i;
            nres[j] %= 5;
        }
        ret = min(ret, f(Hash(nres), idx + 1) + i);
    }
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

	init();

    input();

    int ans = f(Hash(a), 0);
    cout << (ans == INF ? -1 : ans);

	return 0;
}