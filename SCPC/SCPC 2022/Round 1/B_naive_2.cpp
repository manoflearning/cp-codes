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

const int N = 5050;

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

int n, k, x, mx;
vt<int> a, b, nidx[5050];
int dp[5050];

void init() {
    n = k = x = mx = 0;
    b.clear();
    FOR(5050) {
        nidx[i].clear();
        dp[i] = -1;
    }
}

int f(int idx) {
    int& ret = dp[idx];
    if (ret != -1) return ret;
    int val = b[idx - 1];
    if (val == mx) return ret = 1;

    ret = 0;
    /*if (upper_bound(all(nidx[val]), idx) != nidx[val].end()) {
        int l = idx, r = *upper_bound(all(nidx[val]), idx);

        int L = upper_bound(all(nidx[val + 1]), l) - nidx[val + 1].begin();
        int R = upper_bound(all(nidx[val + 1]), r) - nidx[val + 1].begin();
        
        FOR(i, L, R) ret = (ret + f(nidx[val + 1][i])) % MOD;

        ret = (ret + f(r)) % MOD;
    }
    else {
        if (upper_bound(all(nidx[val + 1]), idx) == nidx[val + 1].end()) return ret = 0;

        int L = upper_bound(all(nidx[val + 1]), idx) - nidx[val + 1].begin();
        FOR(i, L, sz(nidx[val + 1])) ret = (ret + f(nidx[val + 1][i])) % MOD;
    }*/

    int lb = upper_bound(all(nidx[val + 1]), idx) - nidx[val + 1].begin();
    FOR(i, lb, sz(nidx[val + 1])) ret = (ret + f(nidx[val + 1][i])) % MOD;

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

    ll p = 1000000007;
	InverseofNumber(p);
	InverseofFactorial(p);
	factorial(p);

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << endl;

        init();

        cin >> n >> k;

        a.resize(n + 1);
        FOR(n) cin >> a[i + 1];

        ll sum = 0;
        FOR(i, 1, n + 1) sum += a[i];

        if (sum % k) {
            cout << 0 << endl;
            continue;
        }
        if (sum == 0) {
            ll cnt = 0;
            sum = 0;
            FOR(i, 1, n + 1) {
                sum += a[i];
                if (sum == 0) cnt++;
            }

            if (cnt >= k) cout << Binomial(cnt - 1, k - 1, MOD) << endl;
            else cout << 0 << endl;
            continue;
        }

        if (sum < 0) {
            sum *= -1;
            FOR(i, 1, n + 1) a[i] *= -1;
        }

        ll x = sum / k;
        sum = 0;
        
        FOR(i, 1, n + 1) {
            sum += a[i];
            if (sum % x == 0 && sum / x <= k) {
                b.push_back(sum / x);
                nidx[sum / x].push_back(sz(b));
                mx = max<int>(mx, sum / x);
            }
        }

        if (sz(nidx[mx]) >= 2) {
            swap(nidx[mx][0], nidx[mx][sz(nidx[mx]) - 1]);
            nidx[mx].erase(nidx[mx].begin() + 1, nidx[mx].end());
        }
        
        //EACH(i, b) cout << i << ' ';
        //cout << endl;

        ll ans = 0;
        EACH(i, nidx[1]) {
            ans = (ans + f(i)) % MOD;
        }
        cout << ans << endl;
    }

	return 0;
}