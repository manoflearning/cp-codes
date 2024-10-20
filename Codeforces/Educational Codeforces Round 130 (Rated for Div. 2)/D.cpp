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

int n, dp2[1010][1010];
char dp1[1010];
int last[26];

void init() {
    FOR(1010) dp1[i] = '*';
    FOR(1010) FOR(j, 1010) dp2[i][j] = -1;
    FOR(26) last[i] = -1;
}

char q1(int idx) {
    char& ret = dp1[idx];
    if (ret != '*') return ret;
    cout << "? 1 " << idx << endl;
    fflush(stdout);
    char c; cin >> c;
    return ret = c;
}

int q2(int l, int r) {
    int& ret = dp2[l][r];
    if (ret != -1) return ret;
    if (l == r) return ret = 1;
    cout << "? 2 " << l << ' ' << r << endl;
    fflush(stdout);
    int x; cin >> x;
    return ret = x;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	// freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	// freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    init();

    cin >> n;

    last[q1(1) - 'a'] = 1;
    FOR(i, 2, n + 1) {
        if (q2(1, i - 1) < q2(1, i)) { last[q1(i) - 'a'] = i; continue; }

        vt<pii> pos;
        FOR(j, 26) if (last[j] != -1) pos.push_back({ last[j], j });
        sort(pos.rbegin(), pos.rend());

        int l = 0, r = sz(pos) - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (q2(pos[mid].fr, i) == mid + 1) r = mid;
            else l = mid + 1;
        }
        dp1[i] = (char)(pos[l].sc + 'a');
        last[dp1[i] - 'a'] = i;
    }

    cout << "! ";
    FOR(i, 1, n + 1) cout << dp1[i];
    cout << endl;
    fflush(stdout);

	return 0;
}