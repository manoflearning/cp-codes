#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
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

        vector<ll> b(2 * n);
        for (auto &i : b) {
            cin >> i;
        }
        
        sort(b.rbegin(), b.rend());

        cout << b[0] << ' ';
        ll x = b[0];
        for (int i = 1; i < 2 * n; i++) {
            if (i <= n) {
                x += b[i];
            } else {
                x -= b[i];
            }
        }

        cout << x << ' ' << b[1] << ' ';
        for (int i = 2; i <= n; i++) {
            cout << b[2 * n - i + 1] << ' ' << b[i] << ' ';
        }
        cout << '\n';
    }
}
