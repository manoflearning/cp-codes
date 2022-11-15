#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, d;
ll t[101010], v[101010], dp[101010];


void f(int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[mid];

    for (int i = max(mid, nl); i <= min(mid + d, nr); i++) {
        if (res < (i - mid) * t[i] + v[mid]) {
            res = (i - mid) * t[i] + v[mid];
            idx = i;
        }
    }

    if (l < r) {
        f(l, mid, nl, idx);
        f(mid + 1, r, idx, nr);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= n; i++) cin >> v[i];

    f(1, n, 1, n);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }

    cout << ans;
    /*for (int i = 1; i <= n; i++) {
        ll res = 0, mxIdx = -1;
        for (int j = i; j <= min(i + d, n); j++) {
            if ((j - i) * t[j] + v[i] > res) {
                res = (j - i) * t[j] + v[i];
                mxIdx = j;
            }
        }

        ans = max(ans, res);
        cout << i << ' ' << mxIdx << '\n';
    }

    cout << ans;*/

	return 0;
}