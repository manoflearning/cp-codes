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

struct Matrix {
    vt<vt<int>> a;

    Matrix operator*(const Matrix& rhs) {
        Matrix ret;
        ret.a.resize(sz(a), vt<int>(sz(rhs.a[0])));
        for (int i = 0; i < sz(ret.a); i++) {
            for (int j = 0; j < sz(ret.a[i]); j++) {
                ll sum = 0;
                for (int k = 0; k < sz(a[i]); k++) {
                    sum = (sum + (ll)a[i][k] * rhs.a[k][j]) % MOD;
                }
                ret.a[i][j] = sum;
            }
        }
        return ret;
    }
};

int k, n;
vt<vt<int>> st, res, res2;

void mul(vt<vt<int>>& a, const vt<vt<int>>& b) {
    for (int i = 0; i < sz(a); i++) {
        for (int j = 0; j < sz(b[i]); j++) {
            for (int k = 0; k < sz(a[i]); k++) {
                res2[i][j] = (res2[i][j] + (ll)a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    a = res2;
}

void f(int cnt) {
    if (cnt == 1) {
        res = st;
        return;
    }

    f(cnt / 2);

    mul(res, res);
    if (cnt & 1) mul(res, st);
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

	cin >> k >> n;

    if (n == 1) {
        cout << 1;
        return 0;
    }

    st.resize(k + 2, vt<int>(k + 2));
    res2.resize(k + 2, vt<int>(k + 2));
    FOR(y, k + 2) {
        FOR(x, k + 2) {
            st[y][x] = (x <= y);
        }
    }

    f(n - 1);

    ll ans = 0;
    FOR(k + 2) ans += res[k + 1][i];
    ans %= MOD;

    cout << ans;

	return 0;
}