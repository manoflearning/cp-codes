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

int isFirst(const string& s, int l, int r) {
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') cnt++;
    }
    return cnt == 2;
}

int isSecond(const string& s, int l, int r) {
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') cnt++;
    }
    return cnt == 1;
}

int isSame(const string& s, int l1, int r1, int l2, int r2) {
    int ret = 1;
    FOR(r1 - l1 + 1) {
        if (s[i + l1] != s[i + l2]) ret = 0;
    }
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

	int tc; cin >> tc;
    FOR(t, 1, tc + 1) {
        cout << "Case #" << t << ": ";

        string s; cin >> s;
        int ans = 0;
        for (int i = 1; i <= sz(s) / 2; i++) {
            for (int l = 0; l + i - 1 < sz(s); l++) {
                int r = l + i - 1;
                if (!isFirst(s, l, r)) continue;

                for (int j = r + 1; j < sz(s); j++) {
                    if (!isSecond(s, r + 1, j)) continue;

                    for (int l2 = j + 1; l2 + i - 1 < sz(s); l2++) {
                        int r2 = l2 + i - 1;
                        if (isSame(s, l, r, l2, r2)) ans = 1;
                    }
                }
            }
        }

        if (ans) cout << "Spell!\n";
        else cout << "Nothing.\n";
    }

	return 0;
}