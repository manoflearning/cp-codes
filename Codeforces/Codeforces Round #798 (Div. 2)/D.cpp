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
        int n, m;
        cin >> n >> m;
        vt<vt<int>> a(n + 1, vt<int>());
        FOR(i, 1, n + 1) {
            a[i].push_back(0);
            string s; cin >> s;
            EACH(j, s) a[i].push_back(j == 'B' ? 1 : 0);
        }
        pii p1 = { -1, -1 }, p2 = { -1, -1 }, p3 = { -1, -1 }, p4 = { -1, -1 };
        FOR(i, 1, n + 1) {
            FOR(j, 1, m + 1) {
                if (a[i][j]) {
                    if (p1.fr == -1 || p1.fr - p1.sc < i - j) p1 = { i, j };
                    if (p2.fr == -1 || p2.fr - p2.sc > i - j) p2 = { i, j };
                    if (p3.fr == -1 || p3.fr + p3.sc < i + j) p3 = { i, j };
                    if (p4.fr == -1 || p4.fr + p4.sc > i + j) p4 = { i, j };
                }
            }
        }
        vt<pii> b = { p1, p2, p3, p4 };
        int mx = INF;
        pii ans = { -1, -1 };
        FOR(i, 1, n + 1) {
            FOR(j, 1, m + 1) {
                int d = 0;
                EACH(k, b) d = max(d, abs(k.fr - i) + abs(k.sc - j));
                if (d < mx) { mx = d; ans.fr = i, ans.sc = j; }
            }
        }
        cout << ans.fr << ' ' << ans.sc << '\n';
    }

	return 0;
}