#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 1000000007;

struct Matrix {
    vector<vector<ll>> a;
    Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(sz(a), vector<ll>(sz(rhs.a[0])));
        for (int i = 0; i < sz(a); i++) {
            for (int j = 0; j < sz(rhs.a[0]); j++) {
                for (int k = 0; k < sz(rhs.a); k++) {
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * rhs.a[k][j]) % MOD;
                }
            }
        }
        return ret;
    }
};

int D;

// 학생회관: 0 -> 1, 2
// 진리관: 1 -> 0, 3, 4
// 형남공학관: 2 -> 0, 3
// 한경직기념관: 3 -> 1, 2, 4, 5
// 신양관: 4 -> 1, 3, 5, 6
// 미래관: 5 -> 3, 4, 6, 7
// 전산관: 6 -> 4, 5, 7
// 정보과학관: 7 -> 5, 6

Matrix power(Matrix base, int cnt) {
    if (cnt == 1) return base;
    Matrix res = power(base, cnt / 2);
    Matrix ret = res * res;
    if (cnt & 1) ret = ret * base;
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> D;

    Matrix base;
    base.a = {
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 1, 1, 0, 0, 0 },
        { 1, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 1, 1, 0, 0 },
        { 0, 1, 0, 1, 0, 1, 1, 0 },
        { 0, 0, 0, 1, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 1, 1, 0 }
    };

    Matrix res = power(base, D);
    cout << res.a[7][7];
}