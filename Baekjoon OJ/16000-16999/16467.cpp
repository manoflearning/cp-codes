//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e8 + 7;
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
Matrix matrixPower(const Matrix& val, ll exp) {
    if (exp == 1) return val;
    Matrix res = matrixPower(val, exp / 2);
    Matrix ret = res * res;
    if (exp & 1) ret = ret * val;
    return ret;
}

ll pow2(ll x) {
    if (x == 0) return 1;
    ll res = pow2(x / 2);
    return res * res % MOD * (x & 1 ? 2 : 1) % MOD;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		int k, n;
        cin >> k >> n;

        if (k == 0) {
            cout << pow2(n) << '\n';
            continue;
        }

        vector<ll> arr(k + 1);
        arr[0] = 1;
        for (int i = 1; i <= k; i++) arr[i] = 1;

        if (n <= k) {
            cout << 1 << '\n';
            continue;
        }

        Matrix b;
        b.a.resize(k + 1, vector<ll>(k + 1));
        b.a[0][0] = b.a[0][k] = 1;
        for (int i = 0; i < k; i++) b.a[i + 1][i] = 1;
        /*for (int i = 0; i < k + 1; i++) {
            for (int j = 0; j < k + 1; j++) {
                cout << b.a[i][j] << ' ';
            }
            cout << '\n';
        }*/

        Matrix res = matrixPower(b, n - k);
        /*for (int i = 0; i < k + 1; i++) {
            for (int j = 0; j < k + 1; j++) {
                cout << res.a[i][j] << ' ';
            }
            cout << '\n';
        }*/

        ll ans = 0;
        for (int i = 0; i <= k; i++) {
            ans = (ans + res.a[0][i]) % MOD;
        }

        cout << ans << '\n';
	}

	return 0;
}