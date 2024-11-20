#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a < c) {
        int ans = 0;
        while (a < c) {
            ans += n - b + 1;
            a++, b = 0;
        }

        ans += d - b;
        cout << ans;
    } else {
        cout << d - b;
    }
}
