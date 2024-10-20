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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll dp[13][10000][9 * 12 + 1];

void init() {
    FOR(i, 13) {
        FOR(j, 10000) {
            FOR(k, 9 * 12 + 1) {
                dp[i][j][k] = -1;
            }
        }
    }
}

ll f1(int L, ll P, int S) {
    ll& ret = dp[L][P][S];
    if (ret != -1) return ret;
    if (L == 0) return !(P % S);

    ll ret = 0;
    FOR(digit, 10) {
        ret += f1(L - 1, P * digit, L + digit);
    }

    return ret;
}

ll CountInterestingIntegersWithPrefixOfN(string N, ll P, int S, int digit_index, int is_first_digit) {
    if (digit_index == sz(N)) return !(P % S);

    int digit_start;
    if (is_first_digit) digit_start = 1;
    else digit_start = 0;

    ll count = 0;
}

ll CountInterestingIntegersWithNumberOfDigits(int L) {
    ll count = 0;

    FOR(digit, 1, 10)
        count += f1(L - 1, digit, digit);

    return count;
}

ll CountInterestingIntegers(string N) {
    if (N == 0) return 0;

    ll count = 0;
    FOR(L, 1, sz(N))
        count += CountInterestingIntegersWithNumberOfDigits(L);

    count += CountInterestingIntegersWithPrefixOfN(N, 1, 0, 0, 0, 1);
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

	

	return 0;
}