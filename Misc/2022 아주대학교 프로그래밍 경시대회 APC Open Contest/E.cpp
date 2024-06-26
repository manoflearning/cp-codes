#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int n;
int a[111], sum, lb, rb;
int dp[111][111][5555];

void init() {
    for (int i = 0; i < 111; i++) {
        for (int j = 0; j < 111; j++) {
            for (int k = 0; k < 5555; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
}

int f(int v, int h, int psum) {
    if (psum >= 5555) psum = 5554;

    int& ret = dp[v][h - lb][psum];
    if (ret != -1) return ret;
    if (v == n + 1) {
        return ret = (n * lb + psum == sum ? 0 : INF);
    }

    ret = INF;
    if (h > lb) ret = min(ret, f(v + 1, h - 1, psum + h - lb));
    ret = min(ret, f(v + 1, h, psum + h - lb));
    if (h < rb) ret = min(ret, f(v + 1, h + 1, psum + h - lb));

    ret += abs(a[v] - h);

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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    lb = (sum - n * (n - 1) / 2 + n - 1) / n, rb = (sum + n * (n - 1) / 2) / n;
    if (lb < 1) lb = 1;
    assert(rb - lb <= 100);

    int ans = INF;
    for (int i = lb; i <= rb; i++) {
        ans = min(ans, f(1, i, 0));
    }

    cout << ans / 2;

	return 0;
}