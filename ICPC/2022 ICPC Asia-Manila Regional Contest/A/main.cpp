#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 1'699'741'697;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int x; cin >> x;

    if (x <= -3) {
        cout << -(x + 4) * (x + 4) + 8;
    } else if (x <= 2) {
        cout << -2 * x + 1;
    } else {
        cout << x * x * x + -14 * x + 17;
    }
}