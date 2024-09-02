#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) (int)(a).size()

const int MOD = 1e9 + 7;

ll n, m;

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

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x % MOD;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n >> m;
    
    Matrix base;
    base.a.resize(2, vector<ll>(2));
    base.a[0][0] = 4 * (n - 1);
    base.a[0][1] = 24 * (n - 2);
    base.a[1][0] = 0;
    base.a[1][1] = 12 * n - 16;

    Matrix ans = matrixPower(base, m);

    ll ans1 = (ans.a[1][1] + MOD) % MOD;
    ll ans2 = (ans.a[0][0] * 6 + ans.a[0][1] + MOD) % MOD;
    cout << ans1 << ' ' << ans2;
}
