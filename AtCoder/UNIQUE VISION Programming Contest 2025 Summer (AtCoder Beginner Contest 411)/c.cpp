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

    int n, q;
    cin >> n >> q;

    vector<bool> co(n);
    int ans = 0;

    while (q--) {
        int x; cin >> x;
        x--;

        if (co[x] == 0) {
            co[x] = 1;
            
            if (0 <= x - 1 && x + 1 < n && co[x - 1] && co[x + 1]) {
                ans -= 1;
            } else if (0 <= x - 1 && co[x - 1]) {
                ans += 0;
            } else if (x + 1 < n && co[x + 1]) {
                ans += 0;
            } else {
                ans += 1;
            }
        } else {
            co[x] = 0;

            if (0 <= x - 1 && x + 1 < n && co[x - 1] && co[x + 1]) {
                ans += 1;
            } else if (0 <= x - 1 && co[x - 1]) {
                ans += 0;
            } else if (x + 1 < n && co[x + 1]) {
                ans += 0;
            } else {
                ans -= 1;
            }
        }

        cout << ans << '\n';
    }
}
