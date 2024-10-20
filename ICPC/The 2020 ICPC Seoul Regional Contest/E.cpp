#include <bits/stdc++.h>
using namespace std;

int n, a[1010101];
int dp[1010101][2][2];

int f(int idx, int b1, int b2) {
    int& ret = dp[idx][b1][b2];
    if (ret != -1) return ret;
    if (idx == n) {
        if (a[idx] == 0) return ret = (b1 == b2);
        if (a[idx] == 1) return ret = (b1 != b2);
        if (a[idx] == 2) return ret = 0;
    }

    ret = 0;
    if (b1 == b2) {
        if (a[idx] == 0) {
            ret |= f(idx + 1, 0, 0);
            ret |= f(idx + 1, 1, 1);
        }
        if (a[idx] == 1) {
            ret |= f(idx + 1, 1, 0);
            ret |= f(idx + 1, 0, 1);
        }
        if (a[idx] == 2) ret = 0;
    }
    if (b1 > b2) {
        if (a[idx] == 0) {
            ret |= f(idx + 1, 1, 0);
        }
        if (a[idx] == 1) {
            ret |= f(idx + 1, 0, 0);
            ret |= f(idx + 1, 1, 1);
        }
        if (a[idx] == 2) {
            ret |= f(idx + 1, 0, 1);
        }
    }
    if (b1 < b2) {
        if (a[idx] == 0) {
            ret |= f(idx + 1, 0, 1);
        }
        if (a[idx] == 1) {
            ret |= f(idx + 1, 0, 0);
            ret |= f(idx + 1, 1, 1);
        }
        if (a[idx] == 2) {
            ret |= f(idx + 1, 1, 0);
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 1010101; i++) {
        dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = -1;
    }

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int ans = 1;
    for (int i = 1; i <= n; i++)
        if (a[i] > 2) ans = 0;

    if (!ans) {
        cout << "NO";
        return 0;
    }

    ans = 0;
    if (a[1] == 0) {
        if (f(2, 0, 0)) ans = 1;
        if (f(2, 1, 1)) ans = 1;
    }
    if (a[1] == 1) {
        if (f(2, 1, 0)) ans = 1;
        if (f(2, 0, 1)) ans = 1;
    }

    cout << (ans ? "YES" : "NO");

    return 0;
}