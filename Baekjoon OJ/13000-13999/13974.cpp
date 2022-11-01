#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n;
ll a[5050], dp[5050][5050], psum[5050];

void init() {
    
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            psum[i] = a[i] + psum[i - 1];
        }

        for (int i = 1; i <= n; i++) dp[i][i] = 0;

        for (int len = 2; len <= n; len++) {
            for (int l = 1; l + len - 1 <= n; l++) {
                int r = l + len - 1;
                
                dp[l][r] = INF;

                for (int i = l; i < r; i++) {
                    dp[l][r] = min(dp[l][r], dp[l][i] + dp[i + 1][r]);
                }

                dp[l][r] += psum[r] - psum[l - 1];
            }
        }

        cout << dp[1][n] << '\n';
    }

    return 0;
}