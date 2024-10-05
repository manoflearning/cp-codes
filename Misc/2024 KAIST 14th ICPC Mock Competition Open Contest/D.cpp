#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;
const int MOD = 998'244'353;

int n;
ll ans[MAXN << 1];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    ans[1] = 1e9;
    for (int i = 1; i <= n + 2; i += 2) {
        ans[i + 1] = ans[i] + (2 * (n + 1) - i);
        ans[i + 2] = ans[i + 1] - i;
    }
    for (int i = 1; i <= n + 2; i++) {
        assert(1 <= ans[i] && ans[i] <= 1e18);
        cout << ans[i] << ' ';
    }
}
