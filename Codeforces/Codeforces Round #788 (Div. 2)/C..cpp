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

int n, v[101010];
vt<pair<pii, int>> a;
ll p2[101010];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
    p2[0] = 1;
    FOR(i, 1, 101010) p2[i] = 2 * p2[i - 1] % MOD;

	int tc; cin >> tc;

    while (tc--) {
        int n; cin >> n;
        a.resize(n + 1);
        FOR(i, 1, n + 1) cin >> a[i].fr.fr;
        FOR(i, 1, n + 1) cin >> a[i].fr.sc;
        FOR(i, 1, n + 1) cin >> a[i].sc;

        sort(a.begin() + 1, a.end());

        ll x = 0, y = 0;
        FOR(n) {
            if (v[i]) continue;
            v[i] = 1;

            int b1 = (a[i].sc > 0), b2 = 1;

            int idx = a[i].fr.sc;
            while (idx != i) {
                b1 |= (a[idx].sc > 0), b2 = 0;

                v[idx] = 1;
                idx = a[idx].fr.sc;
            }

            x++, y += (b1 | b2);
        }

        cout << p2[x - y] << '\n';

        FOR(n + 1) v[i] = 0;
    }

	return 0;
}