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

string s;

int f(int a, int b) {
    int bit = -1;
    EACH(i, s) {
        if (i - 'a' == a) {
            if (bit == 0) return 0;
            bit = 0;
        }
        if (i - 'a' == b) {
            if (bit == 1) return 0;
            bit = 1;
        }
    }

    return 1;
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

	int tc; cin >> tc;

    FOR(tc) {
        cin >> s;

        int ans = 1;

        vt<int> visited(26);
        EACH(c, s) visited[c - 'a']++;

        FOR(26) {
            if (!visited[i]) continue;
            FOR(j, i + 1, 26) {
                if (!visited[j]) continue;

                ans &= f(i, j);
            }
        }

        if (ans) cout << "YES\n";
        else cout << "NO\n";

        /*vt<int> cnt(26), visited(26);
        vt<vt<int>> psum(26, vt<int>(sz(s)));

        EACH(c, s) visited[c - 'a'] = 1;

        FOR(i, sz(s)) {
            FOR(j, 26) {
                if (i > 0) psum[j][i] += psum[j][i - 1];
            }

            psum[s[i] - 'a'][i]++;
            cnt[s[i] - 'a']++;

            int mn = INF, mx = -INF;
            FOR(j, 26) {
                if (!visited[j]) continue;
                mn = min(mn, cnt[j]);
                mx = max(mx, cnt[j]);
            }

            if (mx - mn >= 2) ans = 0;
        }*/
    }

	return 0;
}