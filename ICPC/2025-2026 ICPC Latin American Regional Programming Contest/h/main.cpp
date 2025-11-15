#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    int ans = 0, prv = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (prv < x) {
            prv = x;
            ans++;
        }
    }

    cout << ans;
}