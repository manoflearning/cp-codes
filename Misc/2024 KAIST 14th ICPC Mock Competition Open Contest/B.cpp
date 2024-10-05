#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        if (n <= 5) cout << -1 << '\n';
        else if (n & 1) {
            int m = (n + 1) / 2;
            cout << 4 << '\n';
            cout << 1 << ' ' << m - 1 << ' ' << m << ' ' << 2 * m - 3 << '\n';
        }
        else {
            int m = n / 2;
            cout << 3 << '\n';
            cout << 1 << ' ' << m << ' ' << m + 1 << '\n';
        }
    }
}
