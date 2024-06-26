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

string s, t;
int Q;
vt<string> q;
int isS[17 + 18 * 17 + 1], isS1[18];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> s >> t;
    cin >> Q;
    q.resize(Q);
    EACH(i, q) cin >> i;

    FOR(i, 18) {
        char c1 = 'a' + i;
        string ss, tt;
        EACH(c, s) {
            if (c == c1) ss.push_back(c);
        }
        EACH(c, t) {
            if (c == c1) tt.push_back(c);
        }

        if (ss == tt) isS1[i] = 1;
        else isS1[i] = 0;
    }

    FOR(i, 18) {
        FOR(j, i + 1, 18) {
            char c1 = 'a' + i, c2 = 'a' + j;
            string ss, tt;
            EACH(c, s) {
                if (c == c1 || c == c2) ss.push_back(c);
            }
            EACH(c, t) {
                if (c == c1 || c == c2) tt.push_back(c);
            }

            if (ss == tt) isS[i + 18 * j] = 1;
            else isS[i + 18 * j] = 0;
        }
    }

    EACH(k, q) {
        if (sz(k) == 1) {
            if (isS1[k[0] - 'a']) cout << 'Y';
            else cout << 'N';
            continue;
        }

        ll ans = 1;
        FOR(i, sz(k)) {
            FOR(j, i + 1, sz(k)) {
                int n1 = k[i] - 'a', n2 = k[j] - 'a';
                if (!isS[n1 + 18 * n2]) ans = 0;
            }
        }
        if (ans) cout << 'Y';
        else cout << 'N';
    }

	return 0;
}