#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MOD = 1e9 + 7;
const ll INF = 1e18;

int N, M;

struct Matrix {
    vector<vector<ll>> a;
    Matrix matmul(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(M, vector<ll>(M));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < M; k++) {
                    ret.a[i][j] += a[i][k] * rhs.a[k][j];
                    ret.a[i][j] %= MOD;
                }
            }
        }
        return ret;
    }
};

Matrix I;

Matrix pow_ma(const Matrix& base, int cnt) {
    if (cnt == 0) return I;
    if (cnt == 1) return base;

    Matrix res = pow_ma(base, cnt / 2);
    Matrix ret = res.matmul(res);
    if (cnt & 1) ret = ret.matmul(base);
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    Matrix odd, even;
    odd.a.resize(M, vector<ll>(M));
    even.a.resize(M, vector<ll>(M));
    I.a.resize(M, vector<ll>(M));
    for (int i = 0; i < M; i++) {
        if (i - 1 >= 0) {
            odd.a[i][i - 1] = 1;
            even.a[i][i - 1] = 1;
        }
        even.a[i][i] = 1;
        I.a[i][i] = 1;
        if (i + 1 < M) {
            odd.a[i][i + 1] = 1;
            even.a[i][i + 1] = 1;
        }
    }

    Matrix base = even.matmul(odd);

    Matrix res = pow_ma(base, (N - 1) / 2);
    if (N % 2 == 0) res = odd.matmul(res);

    ll ans = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            ans = (ans + res.a[i][j]) % MOD;
        }
    }

    cout << ans;
}