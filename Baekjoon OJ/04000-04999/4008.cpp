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

struct lf { // f(x) = px + q, x >= s;
    ll p, q;
    double s;
    lf() : lf(1, 0) {}
    lf(ll sp, ll sq) : p(sp), q(sq), s(0) {}
};

double cross(const lf& u, const lf& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}

int n;
ll a, b, c;
ll x[1010101], p[1010101], dp[1010101];
lf ch[1010101];

ll cal(ll x) {
    return a * x * x + b * x + c;
}

void convexHullTrick() {
    int top = 1;
    dp[1] = a * x[1] * x[1] + b * x[1] + c;
    for (int i = 2; i <= n; i++) {
        lf g(-2 * a * p[i - 1] + b, a * p[i - 1] * p[i - 1] - b * p[i - 1] + dp[i - 1]);
        while (top > 1) {
            g.s = cross(ch[top - 1], g);
            if (ch[top - 1].s < g.s) break;
            --top;
        }
        ch[top++] = g;

        ll x = p[i];
        int fpos = top - 1;
        if (x < ch[top - 1].s) {
            
        }
    }

    // a * (p[i] - p[j]) * (p[i] - p[j]) + b * (p[i] - p[j]) + c + dp[j]
    // = (-2 * a * p[j] + b) * p[i] + (a * p[j]^2 - b * p[j] + dp[j]) + (a * p[i]^2 + c)
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

	cin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        p[i] = x[i] + p[i - 1];
    }

    convexHullTrick();

    cout << dp[n];

	return 0;
}