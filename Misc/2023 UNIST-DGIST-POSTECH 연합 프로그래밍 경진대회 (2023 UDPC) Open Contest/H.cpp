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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
ll a[5050];
ll dp[10][10][10][5050];

void init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                memset(dp[i][j][k], -1, sizeof(dp[i][j][k]));
            }
        }
    }
}

int d(int u, int v) {
    int ret = abs(u - v);
    ret = min(ret, abs(u + 10 - v));
    ret = min(ret, abs(v + 10 - u));
    return ret;
}

ll f(int x, int y, int z, int idx) {
    ll& ret = dp[x][y][z][idx];
    if (ret != -1) return ret;
    if (idx == n + 1) return ret = 0;

    ret = INF;
    int v = a[idx];
    ret = min(ret, d(x, v) + f(v, y, z, idx + 1));
    ret = min(ret, d(y, v) + f(x, v, z, idx + 1));
    ret = min(ret, d(z, v) + f(x, y, v, idx + 1));
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    cout << f(0, 0, 0, 1);

    return 0;
}