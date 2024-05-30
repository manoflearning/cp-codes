#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int D = 30;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n, m;

struct Matrix {
    vector<vector<ll>> a;
    Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(m + 1, vector<ll>(m + 1));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= m; k++) {
                    ret.a[i][k] = (ret.a[i][k] + a[i][j] * rhs.a[j][k]) % MOD;
                }
            }
        }
        return ret;
    }
};

Matrix base;

Matrix pm(ll x) {
    if (x == 1) return base;
    Matrix res = pm(x / 2);
    res = res * res;
    if (x & 1) res = res * base;
    return res;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;

    if (n == 1) {
        cout << m;
        return 0;
    }

    // base case
    base.a.resize(m + 1, vector<ll>(m + 1));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (gcd(i, j) == 1) base.a[i][j] = 1;
        }
    }

    // solve
    Matrix ans = pm(n - 1);

    ll sum = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            // cout << i << ' ' << j << ' ' << ans[i][j] << '\n';
            sum = (sum + ans.a[i][j]) % MOD;
        }
    }

    cout << sum;
}