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
const int MOD = 1'000'000'000;
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

Matrix base;

Matrix matrixPower(ll exp) {
    if (exp == 1) return base;
    Matrix res = matrixPower(exp / 2);
    Matrix ret = res * res;
    if (exp & 1) ret = ret * base;
    return ret;
}

ll a, b;

ll f(ll x) {
    if (x == 0) return 0;
    Matrix res = matrixPower(x);
    return (res.a[0][0] + res.a[0][1] + MOD - 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> a >> b;

    base.a.resize(2, vector<ll>(2));
    base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;

    cout << (f(b) - f(a - 1) + MOD) % MOD;
}