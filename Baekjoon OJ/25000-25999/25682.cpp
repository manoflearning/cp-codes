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

const int MAX = 2020;

int n, m, k;

string a[MAX];
int psum[MAX][MAX], psum2[MAX][MAX];

void buildPsum() {
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            int bit = ((i + j) & 1) ^ (a[i][j] == 'B');

            psum[i][j] += bit;
            psum[i][j] += psum[i][j - 1];
            psum[i][j] += psum[i - 1][j];
            psum[i][j] -= psum[i - 1][j - 1];

            int bit2 = ((i + j) & 1) ^ (a[i][j] == 'W');

            psum2[i][j] += bit2;
            psum2[i][j] += psum2[i][j - 1];
            psum2[i][j] += psum2[i - 1][j];
            psum2[i][j] -= psum2[i - 1][j - 1];
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

	cin >> n >> m >> k;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        a[i].push_back('B');
        for (int j = m - 1; j >= 0; j--) {
            a[i][j + 1] = a[i][j];
        }
    }

    buildPsum();
    
    int ans = INF;
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= m; j++) {
            int res = psum[i][j] - psum[i - k][j] - psum[i][j - k] + psum[i - k][j - k];
            int res2 = psum2[i][j] - psum2[i - k][j] - psum2[i][j - k] + psum2[i - k][j - k];
            ans = min({ ans, res, res2 });
        }
    }

    cout << ans;

	return 0;
}