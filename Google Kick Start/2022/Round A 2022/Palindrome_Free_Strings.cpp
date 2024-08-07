#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
string s1, s2;

int f(int p) {
    if (p == n) return 1;

    int ret = 0;
    if (s1[p] == '?') {
        char c = '2';
        if (p >= 4 && s2[p - 3] == s2[p - 1]) {
            if (s2[p - 4] == '0') c = '1';
            else c = '0';
        }
        if (p >= 5 && s2[p - 4] == s2[p - 1] && s2[p - 3] == s2[p - 2]) {
            if (s2[p - 5] == '0') {
                if (c == '0') return 0;
                c = '1';
            }
            else {
                if (c == '1') return 0;
                c = '0';
            }
        }

        if (c == '2') {
            s2.push_back('0');
            ret |= f(p + 1);
            s2.pop_back();

            s2.push_back('1');
            ret |= f(p + 1);
            s2.pop_back();
        }
        else {
            s2.push_back(c);
            ret |= f(p + 1);
            s2.pop_back();
        }
    }
    else {
        if (p >= 4 && s2[p - 3] == s2[p - 1] && s2[p - 4] == s1[p]) return 0;
        if (p >= 5 && s2[p - 4] == s2[p - 1] && s2[p - 3] == s2[p - 2] && s2[p - 5] == s1[p]) return 0;

        s2.push_back(s1[p]);
        ret |= f(p + 1);
        s2.pop_back();
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

	FOR(tc) {
        s2.clear();
        cin >> n >> s1;

        cout << "Case #" << i + 1 << ": ";
        if (n <= 4 || f(0)) cout << "POSSIBLE";
        else cout << "IMPOSSIBLE";
        cout << '\n';
	}

	return 0;
}