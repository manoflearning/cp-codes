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

int n, m;
vt<vt<int>> a;
vt<pair<int, pii>> b;

void init() {
    n = m = 0;
    a.clear();
    b.clear();
}

int dist(int x, pii y) {
    return max(abs(x - y.fr), abs(x - y.sc));
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

    while (tc--) {
        init();

        cin >> n >> m;
        a.resize(n + 1, vt<int>(m + 1));
        FOR(i, 1, n + 1) {
            string s; cin >> s;
            FOR(j, sz(s)) {
                a[i][j + 1] = (s[j] == 'B');
            }
        }

        FOR(i, 1, n + 1) {
            int l = -1, r = -1;
            FOR(j, 1, m + 1) {
                if (a[i][j]) {
                    if (l == -1) l = j;
                    r = j;
                }
            }
            if (l != -1) {
                b.push_back({ i, { l, r }});
            }
        }

        int mn = INF;
        pii ans = { -1, -1 };
        FOR(x, 1, m + 1) {
            vt<int> pmx(sz(b)), rpmx(sz(b));
            pmx[0] = dist(x, b[0].sc);
            FOR(i, 1, sz(b)) {
                pmx[i] = max(pmx[i - 1] + (b[i].fr - b[i - 1].fr), dist(x, b[i].sc));
            }

            rpmx[sz(b) - 1] = dist(x, b[sz(b) - 1].sc);
            FOR(i, sz(b) - 2, -1, -1) {
                rpmx[i] = max(rpmx[i + 1] + (b[i + 1].fr - b[i].fr), dist(x, b[i].sc));
            }

            FOR(i, sz(b) - 1) {
                if (b[i].fr == b[i + 1].fr) continue;

                int len = (b[i + 1].fr - b[i].fr), diff = abs(pmx[i] - rpmx[i + 1]);
                int res = min(pmx[i], rpmx[i + 1]) + diff + (len - diff) / 2 + ((len - diff) & 1);
                //cout << len << ' ' << diff << ' ' << res << '\n';
                if (res < mn) {
                    mn = res;
                    ans.fr = b[i].fr + (pmx[i] < rpmx[i + 1] ? diff + (len - diff) / 2 + ((len - diff) & 1) : len - diff - (len - diff) / 2 - ((len - diff) & 1));
                    ans.sc = x;
                }
            }
        }

        cout << ans.fr << ' ' << ans.sc << '\n';
        cout << mn << '\n';
    }

	return 0;
}