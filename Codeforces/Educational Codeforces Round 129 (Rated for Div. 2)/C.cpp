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
        int n; cin >> n;

        vt<pair<pii, int>> a(n);
        EACH(i, a) cin >> i.fr.fr;
        EACH(i, a) cin >> i.fr.sc;

        FOR(n) a[i].sc = i;

        vt<pair<pii, int>> b = a;

        sort(all(b));

        int imp = 0;
        FOR(i, n - 1) {
            if (b[i].fr.sc > b[i + 1].fr.sc) imp = 1;
        }

        if (imp) {
            cout << -1 << '\n';
            continue;
        }

        vt<int> c, d;
        FOR(n) {
            c.push_back(a[i].sc);
            d.push_back(b[i].sc);
        }

        vt<pii> ans;
        FOR(i, n - 1, -1, -1) {
            int idx = 0;
            FOR(j, n) if (d[i] == c[j]) idx = j;

            FOR(j, idx, i) {
                ans.push_back({ j, j + 1 });
                swap(c[j], c[j + 1]);
            }
        }

        /*EACH(i, c) cout << i << ' ';//cout << a[i].fr.fr << ' ';
        cout << '\n'; 
        EACH(i, d) cout << i << ' ';//cout << a[i].fr.sc << ' ';
        cout << '\n';*/

        cout << sz(ans) << '\n';
        EACH(i, ans) cout << i.fr + 1 << ' ' << i.sc + 1 << '\n';
    }

	return 0;
}