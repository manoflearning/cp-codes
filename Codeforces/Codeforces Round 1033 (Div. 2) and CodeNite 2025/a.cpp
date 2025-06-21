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
        vector<int> l(3), d(3);
        for (int i = 0; i < 3; i++) {
            cin >> l[i] >> d[i];
        }

        bool ans = 0;
        if (l[0] + l[1] + l[2] == d[0] && d[0] == d[1] && d[1] == d[2]) {
            ans = 1;
        }
        if (d[0] + d[1] + d[2] == l[0] && l[0] == l[1] && l[1] == l[2]) {
            ans = 1;
        }
        if (l[0] == l[1] + l[2] && d[0] + d[1] == l[0] && d[1] == d[2]) {
            ans = 1;
        }
        if (d[0] == d[1] + d[2] && l[0] + l[1] == d[0] && l[1] == l[2]) {
            ans = 1;
        }

        cout << (ans ? "YES" : "NO") << '\n';
    }
}
