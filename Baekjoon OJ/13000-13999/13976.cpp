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

struct Matrix {
	vector<vector<ll>> a;
	Matrix operator*(const Matrix& rhs) const {
		Matrix ret;
		ret.a.resize(sz(a), vector<ll>(sz(rhs.a[0])));
		for (int y = 0; y < sz(ret.a); y++) {
			for (int x = 0; x < sz(ret.a[y]); x++) {
				ll sum = 0;
				for (int i = 0; i < sz(a[y]); i++) {
					sum = (sum + a[y][i] * rhs.a[i][x]) % MOD;
				}
				ret.a[y][x] = sum;
			}
		}
		return ret;
	}
};

ll n, dp[10101];

Matrix m;

Matrix cal(ll cnt) {
    if (cnt == 1) return m;
    
    Matrix res = cal(cnt / 2);
    Matrix ret = res * res;
    if (cnt & 1) ret = ret * m;

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;

    if (n & 1) {
        cout << 0;
        return 0;
    }
    if (n == 2) {
        cout << 3;
        return 0;
    }

    n >>= 1;

    m.a.resize(2, vector<ll>(2));
    m.a[0][0] = 4, m.a[0][1] = -1;
    m.a[1][0] = 1, m.a[1][1] = 0;

    Matrix ma = cal(n - 1);
    
    ll ans = ((ma.a[0][0] * 3 + ma.a[0][1] * 1) % MOD + MOD) % MOD;
    cout << ans % MOD;

	return 0;
}