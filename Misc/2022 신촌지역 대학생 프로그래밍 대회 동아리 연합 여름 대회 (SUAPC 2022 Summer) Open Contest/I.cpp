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

const int MAX = 3030;

int n, m, k;
int a[3030][3030], psum[MAX][MAX];
int cnt[3030][3030];
vector<pii> ans;

void buildPsum() {
      FOR(i, 1, MAX) {
            FOR(j, 1, MAX) {
                  psum[i][j] += a[i][j];
                  psum[i][j] += psum[i][j - 1];
                  psum[i][j] += psum[i - 1][j];
                  psum[i][j] -= psum[i - 1][j - 1];
            }
      }
}

int query(int sy, int sx, int ey, int ex) {
    if (sy < 1 || sx < 1) return 0;
    if (ey > n || ex > m) return 0;

    int ret = psum[ey][ex];
    ret -= psum[ey][sx - 1];
    ret -= psum[sy - 1][ex];
    ret += psum[sy - 1][sx - 1];

    return ret;
}

void input() {
    cin >> n >> m >> k;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> a[i][j];
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    if (k == 1) {
        vt<pii> ans;
        FOR(i, 1, n + 1) {
            FOR(j, 1, m + 1) {
                if (a[i][j]) ans.push_back({ i, j });
            }
        }

        if (sz(ans) == 2) cout << 0;
        else {
            cout << 1 << '\n';
            cout << ans[0].fr << ' ' << ans[0].sc;
        }

        return 0;
    }
    if (k == 2) {
        vt<pii> ans;
        FOR(i, 1, n + 1) {
            FOR(j, 1, m + 1) {
                if (a[i][j]) ans.push_back({ i, j });
            }
        }

        if (sz(ans) == 2) {
            cout << 2 << '\n';
            cout << ans[0].fr << ' ' << ans[0].sc << '\n';
            cout << ans[1].fr << ' ' << ans[1].sc << '\n';
        }
        else if (sz(ans) == 3) {
            cout << 1 << '\n';
            EACH(i, ans) {
                int y = i.fr, x = i.sc;
                int res = 0;
                FOR(j, 4) {
                    int ny = y + dy[j], nx = x + dx[j];
                    if (a[ny][nx]) res++;
                }

                if (res == 2) {
                    cout << y << ' ' << x;
                    break;
                }
            }
        }
        else cout << 0;

        return 0;
    }

    buildPsum();

    int cas = 0;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            if (query(i, j, i + k - 1, j) == k) {
                if (i + k <= n && a[i + k][j] && a[i - 1][j]) continue;
                cas++;
                FOR(y, i, i + k) {
                    if (cnt[y][j]) ans.push_back({ y, j });
                    cnt[y][j]++;
                }
            }
            if (query(i, j, i, j + k - 1) == k) {
                if (j + k <= m && a[i][j + k] && a[i][j - 1]) continue;
                cas++;
                FOR(x, j, j + k) {
                    if (cnt[i][x]) ans.push_back({ i, x });
                    cnt[i][x]++;
                }
            }
        }
    }

    if (cas == 2) {
        cout << sz(ans) << '\n';
        sort(all(ans));
        EACH(i, ans)
            cout << i.fr << ' ' << i.sc << '\n';
    }
    else {
        FOR(i, 1, n + 1) {
            FOR(j, 1, m + 1) {
                if (cnt[i][j]) ans.push_back({ i, j });
            }
        }

        cout << sz(ans) << '\n';
        EACH(i, ans)
            cout << i.fr << ' ' << i.sc << '\n';
    }

	return 0;
}