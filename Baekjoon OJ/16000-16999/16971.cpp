#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, m;
ll a[1010][1010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    int mnir = -1, mxir = -1;
    ll mnr = INF, mxr = -INF;

    for (int i = 1; i <= n; i++) {
        ll sum = 0;
        for (int j = 1; j <= m; j++) {
            sum += (j == 1 || j == m ? 1 : 2) * a[i][j];
        }
        
        if ((i == 1 || i == n) && sum > mxr) {
            mxr = sum; mxir = i;
        }
        if (2 <= i && i <= n - 1 && sum < mnr) {
            mnr = sum; mnir = i;
        }
    }

    int mnic = -1, mxic = -1;
    ll mnc = INF, mxc = -INF;
    
    for (int j = 1; j <= m; j++) {
        ll sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += (i == 1 || i == n ? 1 : 2) * a[i][j];
        }

        if ((j == 1 || j == m) && sum > mxc) {
            mxc = sum; mxic = j;
        }
        if (2 <= j && j <= m - 1 && sum < mnc) {
            mnc = sum; mnic = j;
        }
    }

    if (mxr <= mnr && mxc <= mnc);
    else if (mxr - mnr >= mxc - mnc) {
        for (int j = 1; j <= m; j++) {
            swap(a[mnir][j], a[mxir][j]);
        }
    }
    else {
        for (int i = 1; i <= n; i++) {
            swap(a[i][mnic], a[i][mxic]);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i == 1 || i == n) && (j == 1 || j == m)) ans += a[i][j];
            else if ((i == 1 || i == n) || (j == 1 || j == m)) ans += 2 * a[i][j];
            else ans += 4 * a[i][j];
        }
    }

    cout << ans;

	return 0;
}