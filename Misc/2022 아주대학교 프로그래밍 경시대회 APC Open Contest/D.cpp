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
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

int m, mod;
vt<int> a;
vt<ll> dp[5050];

void input() {
    cin >> m >> mod;
    for (int i = 1; i <= m; i++) {
        string s = to_string(i);
        int sum = 0;
        for (auto& c : s) sum += c - '0';
        if (gcd(i, sum) == sum) 
            a.push_back(i);
    }
}

ll f(int v, int lb) {
    ll& ret = dp[v][lb];
    if (ret != -1) return ret;
    if (v == m && lb == sz(a)) return 1;

    ret = 0;
    if (lb < sz(a) && v + a[lb] <= m) ret = (ret + f(v + a[lb], lb)) % mod;
    if (lb < sz(a)) ret = (ret + f(v, lb + 1)) % mod;

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    for (int i = 0; i < 5050; i++) {
        dp[i].resize(sz(a) + 1, -1);
    }

    cout << f(0, 0) << '\n';

	return 0;
}