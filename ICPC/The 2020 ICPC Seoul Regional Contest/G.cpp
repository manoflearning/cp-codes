#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int n;
ll d;
ll a[1010101], b[1010101], c[1010101];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        b[i] = a[i] - a[1] - (i - 1) * d;
        c[i] = a[i] - a[n] - (n - i) * d;
    }

    ll mx = -LLONG_MIN, mn = LLONG_MAX;
    ll mx2 = -LLONG_MIN, mn2 = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, b[i]);
        mn = min(mn, b[i]);
        mx2 = max(mx2, c[i]);
        mn2 = min(mn2, c[i]);
    }

    ll ans = min(mx - mn, mx2 - mn2);
    if (ans % 2 == 0) cout << ans / 2 << ".0";
    else cout << ans / 2 << ".5";

    return 0;
}