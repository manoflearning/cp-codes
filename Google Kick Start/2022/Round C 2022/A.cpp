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

    FOR(t, 1, tc + 1) {
        cout << "Case #" << t << ": ";

        int n;
        string s;
        cin >> n >> s;

        int b2 = 0, b3 = 0, b4 = 0, b5 = 0;
        FOR(n) {
            if ('A' <= s[i] && s[i] <= 'Z') b2 = 1;
            if ('a' <= s[i] && s[i] <= 'z') b3 = 1;
            if ('0' <= s[i] && s[i] <= '9') b4 = 1;
            if (s[i] == '#' || s[i] == '@' || s[i] == '*' || s[i] == '&') b5 = 1;
        }

        if (!b2) s.push_back('A');
        if (!b3) s.push_back('a');
        if (!b4) s.push_back('0');
        if (!b5) s.push_back('#');

        while (sz(s) < 7) s.push_back('1');

        cout << s << '\n';
    }

	return 0;
}