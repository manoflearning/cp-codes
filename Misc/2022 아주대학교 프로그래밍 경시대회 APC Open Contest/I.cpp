#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n, a[101], allSum;
int dp[101][101][5050];

void init() {
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            for (int k = 0; k < 5050; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
}

int f(int v, int h, int sum) {
    if (sum > n * (n + 1) / 2) sum = n * (n + 1) / 2 + 1;

    int& ret = dp[v][h][sum];
    if (ret != -1) return ret;
    if (v == n + 1) return ret = (sum == allSum ? 0 : INF);

    ret = INF;
    if (h > 1) ret = min(ret, f(v + 1, h - 1, sum + h));
    ret = min(ret, f(v + 1, h, sum + h));
    ret = min(ret, f(v + 1, h + 1, sum + h));

    ret += abs(h - a[v]);

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
        allSum += a[i];
    }

    int ans = INF;
    for (int i = 1; i <= 100; i++) {
        ans = min(ans, f(1, i, 0));
    }

    cout << ans / 2;

	return 0;
}