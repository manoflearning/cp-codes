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
const int MOD = 9999991;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int N = 1000001;

// array to store inverse of 1 to N
ll factorialNumInverse[N + 1];

// array to precompute inverse of 1! to N!
ll naturalNumInverse[N + 1];

// array to store factorial of first N numbers
ll fact[N + 1];

// Function to precompute inverse of numbers
void InverseofNumber(ll p) {
	naturalNumInverse[0] = naturalNumInverse[1] = 1;
	for (int i = 2; i <= N; i++)
		naturalNumInverse[i] = naturalNumInverse[p % i] * (p - p / i) % p;
}
// Function to precompute inverse of factorials
void InverseofFactorial(ll p) {
	factorialNumInverse[0] = factorialNumInverse[1] = 1;

	// precompute inverse of natural numbers
	for (int i = 2; i <= N; i++)
		factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % p;
}

// Function to calculate factorial of 1 to N
void factorial(ll p) {
	fact[0] = 1;

	// precompute factorials
	for (int i = 1; i <= N; i++) {
		fact[i] = (fact[i - 1] * i) % p;
	}
}

// Function to return nCr % p in O(1) time
ll Binomial(ll N, ll R, ll p) {
	// n C r = n!*inverse(r!)*inverse((n-r)!)
	ll ans = ((fact[N] * factorialNumInverse[R])
			% p * factorialNumInverse[N - R])
			% p;
	return ans;
}

int n, a[22], par[22], rt;
pii chd[22];
ll sum[22];

void init() {
    n = 0, rt = 0;
    FOR(22) {
        a[i] = par[i] = 0;
        chd[i] = { -1, -1 };
        sum[i] = 0;
    }
}

void insert(int v, int en) {
    if (en < v) {
        if (chd[v].fr == -1) chd[v].fr = en;
        else insert(chd[v].fr, en);
    }
    if (v < en) {
        if (chd[v].sc == -1) chd[v].sc = en;
        else insert(chd[v].sc, en);
    }
}

ll dfs(int v) {
    sum[v] = 1;
    if (chd[v].fr != -1) sum[v] += dfs(chd[v].fr);
    if (chd[v].sc != -1) sum[v] += dfs(chd[v].sc);
    return sum[v];
}

ll f(int v) {
    if (chd[v].fr == -1 && chd[v].sc == -1) return 1; 
    else if (chd[v].fr == -1) return f(chd[v].sc);
    else if (chd[v].sc == -1) return f(chd[v].fr);

    ll ret = Binomial(sum[chd[v].fr] + sum[chd[v].sc], sum[chd[v].fr], MOD);
    ret = (ret * f(chd[v].fr)) % MOD;
    ret = (ret * f(chd[v].sc)) % MOD;
    
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

    InverseofNumber(MOD);
	InverseofFactorial(MOD);
	factorial(MOD);

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        init();

        cin >> n;
        FOR(i, 1, n + 1) cin >> a[i];

        rt = a[1];
        FOR(i, 2, n + 1) {
            int v = a[i];
            insert(rt, v);
        }

        dfs(rt);

        cout << f(rt) << '\n';
    }

	return 0;
}