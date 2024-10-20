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
    FOR(tt, 1, tc + 1) {
        int odd248 = 0, even248 = 0;
        //set<int> s;
        int x0 = -1, bit = 0;

        int n; cin >> n;
        FOR(n) {
            int x; cin >> x;

            int y = x % 10;
            if (y == 5) {
                if (x0 == -1 || x0 == x + 5) x0 = x + 5;
                else bit = 1;
            }
            else if (y == 0) {
                if (x0 == -1 || x0 == x) x0 = x;
                else bit = 1;
            }
            else {
                while (x % 10 != 2) {
                    x += x % 10;
                }

                int z = x / 10;
                if (z & 1) odd248 = 1;
                else even248 = 1;
            }
        }

        if (bit) cout << "NO\n";
        else if (x0 != -1) {
            if (odd248 || even248) cout << "NO\n";
            else cout << "YES\n";
        }
        else if (odd248 ^ even248) cout << "YES\n";
        else cout << "NO\n";
    }

    // 0 -> (0)
    // 1 -> (2 -> 4 -> 8 -> 6)
    // 3 -> (6 -> 2 -> 4 -> 8)
    // 5 -> (0)
    // 7 -> (4 -> 8 -> 6 -> 2)
    // 9 -> (8 -> 6 -> 2 -> 4)

	return 0;
}