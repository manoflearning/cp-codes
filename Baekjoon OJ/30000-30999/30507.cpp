#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 3;
const array<array<ll, 4>, 4> I = {
    array<ll, 4>{1, 0, 0, 0},
    array<ll, 4>{0, 1, 0, 0},
    array<ll, 4>{0, 0, 1, 0},
    array<ll, 4>{0, 0, 0, 1}
};

array<array<ll, 4>, 4> mul(const array<array<ll, 4>, 4> &lhs, const array<array<ll, 4>, 4> &rhs) {
    array<array<ll, 4>, 4> ret = {
        array<ll, 4>{0, 0, 0, 0},
        array<ll, 4>{0, 0, 0, 0},
        array<ll, 4>{0, 0, 0, 0},
        array<ll, 4>{0, 0, 0, 0}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                ret[i][j] = (ret[i][j] + lhs[i][k] * rhs[k][j]) % MOD;
            }
        }
    }
    return ret;
}

array<array<ll, 4>, 4> exp(array<array<ll, 4>, 4> x, ll y) {
    if (y == 0) return I;
    if (y == 1) return x;
    array<array<ll, 4>, 4> res = exp(x, y / 2);
    return mul(mul(res, res), y & 1 ? x : I);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ll n; cin >> n;

    array<array<ll, 4>, 4> x = {
        array<ll, 4>{1, 0, 1, 1},
        array<ll, 4>{0, 1, 1, 1},
        array<ll, 4>{1, 1, 1, 0},
        array<ll, 4>{1, 1, 0, 1}
    };
    
    auto ans = exp(x, n - 1);
    cout << 4 * (ans[0][0] + ans[0][2] + ans[0][3]) % MOD;
}
