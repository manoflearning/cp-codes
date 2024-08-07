#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;
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

ll n, cnt[6], dp[6];
int m;

Matrix f(ll n, const Matrix& b) {
    if (n == 1) return b;

    Matrix res = f(n / 2, b);
    Matrix ret = res * res;
    if (n & 1) ret = ret * b;
    
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = i - 1; j >= 1; j--) {
            dp[i] = (dp[i] + dp[j] * cnt[i - j]) % MOD;
        }
        dp[i] = (dp[i] + cnt[i]) % MOD;
    }

    if (n <= 5) {
        cout << dp[n];
        return 0;
    }

    Matrix b;
    b.a.resize(5, vector<ll>(5));
    for (int i = 0; i < 5; i++) {
        b.a[0][i] = cnt[i + 1];
    }
    b.a[1][0] = b.a[2][1] = b.a[3][2] = b.a[4][3] = 1;

    Matrix res = f(n - 5, b);

    ll ans = 0;
    ans = (ans + res.a[0][0] * dp[5]) % MOD;
    ans = (ans + res.a[0][1] * dp[4]) % MOD;
    ans = (ans + res.a[0][2] * dp[3]) % MOD;
    ans = (ans + res.a[0][3] * dp[2]) % MOD;
    ans = (ans + res.a[0][4] * dp[1]) % MOD;
    ans = (ans + MOD) % MOD;

    cout << ans;

	return 0;
}