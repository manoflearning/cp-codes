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
        int a, x, y;
        cin >> a >> x >> y;

        bool ans = 0;
        for (int b = -100; b <= 200; b++) {
            if (abs(b - x) < abs(a - x) && abs(b - y) < abs(a - y)) {
                ans = 1;
            }
        }
        cout << (ans ? "YES" : "NO") << '\n';
    }
}
