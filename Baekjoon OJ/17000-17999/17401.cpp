#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll MOD = 1'000'000'007;

int T, N, D;
struct Matrix {
    vector<vector<ll>> a;
    Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(N, vector<ll>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ll res = 0;
                for (int k = 0; k < N; k++)
                    res = (res + a[i][k] * rhs.a[k][j]) % MOD;
                ret.a[i][j] = res % MOD;
            }
        }
        return ret;
    }
};
Matrix ma[111], pma[111];

void input() {
    cin >> T >> N >> D;

    ma[0].a.resize(N, vector<ll>(N));
    for (int x = 0; x < N; x++) ma[0].a[x][x] = 1;

    for (int i = 1; i <= T; i++) {
        int M; cin >> M;
        ma[i].a.resize(N, vector<ll>(N));
        while (M--) {
            int x, y, z;
            cin >> x >> y >> z;
            ma[i].a[x - 1][y - 1] = z;
        }
    }
}

Matrix power(int cnt) {
    if (cnt == 0) return pma[0];
    if (cnt == 1) return pma[T];

    Matrix ret = power(cnt / 2);
    return ret * ret * (cnt & 1 ? pma[T] : pma[0]);
}

void print(const Matrix& ans) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << ans.a[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    pma[0] = ma[0];
    for (int i = 1; i <= T; i++) {
        pma[i] = pma[i - 1] * ma[i];
        // print(pma[i]);
        // cout << '\n';
    }

    // Matrix now = pma[0];
    // for (int i = 1; i <= 10; i++) {
    //     now = ma[i % T == 0 ? T : i % T] * now;
    //     print(now);
    //     cout << '\n';
    // }

    Matrix ans = power(D / T) * pma[D % T];
    print(ans);
}