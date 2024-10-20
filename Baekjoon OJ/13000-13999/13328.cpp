#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 31'991;

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

ll d, t;
ll a[55], arr[55];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> d >> t;

    a[d] = 1;
    for (int i = 1; i <= 50; i++) {
        ll sum = 0;
        for (int j = 1; j <= d; j++) sum = (sum + a[j]) % MOD;
        for (int j = 2; j <= d; j++) a[j - 1] = a[j];
        a[d] = arr[i] = sum;
    }
    
    if (t <= d) {
        cout << arr[t];
        return 0;
    }

    Matrix m;
    m.a.resize(d, vector<ll>(d));
    for (int i = 0; i < d; i++) m.a[0][i] = 1;
    for (int i = 1; i < d; i++) m.a[i][i - 1] = 1;

    Matrix res = matrixPower(m, t - d);
    ll ans = 0;
    for (int i = 0; i < d; i++)
        ans = (ans + res.a[0][i] * arr[d - i]) % MOD;
    cout << ans;
}