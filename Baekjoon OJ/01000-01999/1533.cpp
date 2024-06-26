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
const int MOD = 1000003;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Matrix {
    vt<vt<ll>> a;

    Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(sz(a), vt<ll>(sz(rhs.a[0])));
        for (int i = 0; i < sz(ret.a); i++) {
            for (int j = 0; j < sz(ret.a[i]); j++) {
                ll sum = 0;
                for (int k = 0; k < sz(a[i]); k++) {
                    sum = (sum + a[i][k] * rhs.a[k][j]) % MOD;
                }
                ret.a[i][j] = sum;
            }
        }
        return ret;
    }
};

int n, so, si, t;
int adj[15][15];
Matrix st;

void input() {
    cin >> n >> so >> si >> t;
    so--, si--;
    FOR(n) {
        string s; cin >> s;
        FOR(j, n) {
            adj[i][j] = s[j] - '0';
        }
    }
}

void buildMatrix() {
    st.a.resize(5 * n, vt<ll>(5 * n));

    int prv = n - 1;
    FOR(n) FOR(j, n) {
        int x = adj[i][j];

        if (x == 0) continue;
        if (x == 1) {
            st.a[5 * i][5 * j] = 1;
            continue;
        }

        FOR(k, x - 1) {
            st.a[5 * i + k][5 * i + k + 1] = 1;
        }
        st.a[5 * i + x - 1][5 * j] = 1;
    }

    /*FOR(sz(st.a)) {
        FOR(j, sz(st.a[i])) {
            cout << st.a[i][j] << ' ';
        }
        cout << '\n';
    }*/
}

Matrix f(int cnt) {
    if (cnt == 1) return st;

    Matrix res = f(cnt / 2);
    if (cnt & 1) return res * res * st;
    else return res * res;
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

	input();

    buildMatrix();

    Matrix res = f(t);
    
    cout << res.a[5 * so][5 * si];

	return 0;
}