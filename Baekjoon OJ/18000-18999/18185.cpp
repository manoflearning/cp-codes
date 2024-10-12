#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

int n, a[10101];
int ans = 0;

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
        if (i + 2 <= n) {
            if (a[i + 1] > a[i + 2]) {
                int res = min(a[i + 1] - a[i + 2], a[i]);
                ans += 5 * res;
                a[i] -= res, a[i + 1] -= res;
            }

            int res = min({ a[i], a[i + 1], a[i + 2] });
            ans += 7 * res;
            a[i] -= res, a[i + 1] -= res, a[i + 2] -= res;
        }

        if (i + 1 <= n) {
            int res = min(a[i], a[i + 1]);
            ans += 5 * res;
            a[i] -= res, a[i + 1] -= res;
        }

        ans += 3 * a[i];
        a[i] = 0;
    }

    cout << ans;
}
