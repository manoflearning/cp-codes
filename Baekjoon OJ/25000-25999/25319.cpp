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

int n, m, l;
vt<vt<int>> a;
vt<int> id;
vt<int> cnt(26), cnt2(26);
int c = INF;
vt<vt<int>> vi;
string ans;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> n >> m >> l;
    a.resize(n, vt<int>(m));
    vi.resize(n, vt<int>(m));
    FOR(n) {
        string s; cin >> s;
        FOR(j, m) {
            a[i][j] = s[j] - 'a';
        }
    }
    string s; cin >> s;
    EACH(i, s) id.push_back(i - 'a');

    FOR(n) {
        FOR(j, m) {
            cnt[a[i][j]]++;
        }
    }

    EACH(i, id) cnt2[i]++;
    
    FOR(26) {
        if (cnt2[i]) c = min(c, cnt[i] / cnt2[i]);
    }

    int ny = 0, nx = 0;
    FOR(c) {
        EACH(val, id) {
            FOR(y, n) {
                FOR(x, m) {
                    if (vi[y][x]) continue;
                    if (a[y][x] == val) {
                        vi[y][x] = 1;
                        FOR(abs(y - ny)) ans.push_back((y > ny ? 'D' : 'U'));
                        FOR(abs(x - nx)) ans.push_back((x > nx ? 'R' : 'L'));
                        ny = y, nx = x;
                        y = n, x = m;
                        break;
                    }
                }
            }
            ans.push_back('P');
        }
    }
    FOR(abs(n - 1 - ny)) ans.push_back((n - 1 > ny ? 'D' : 'U'));
    FOR(abs(m - 1 - nx)) ans.push_back((m - 1 > nx ? 'R' : 'L'));

    cout << c << ' ' << sz(ans) << '\n' << ans;

	return 0;
}