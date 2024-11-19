#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;

int n;
ll a[MAXN], lmx[MAXN], rmx[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        if (a[i]) lmx[i] = max(a[i], lmx[i - 1]);
        else lmx[i] = 0;
    }
    for (int i = n; i >= 1; i--) {
        if (a[i]) rmx[i] = max(a[i], rmx[i + 1]);
        else rmx[i] = 0;
    }

    ll ans = 0;
    for (int i = 2; i <= n - 1; i++) {
        if (a[i] == 0) continue;
        int mx = min(lmx[i], rmx[i]);
        if (mx > a[i]) ans += mx - a[i];
    }

    cout << ans;
}
