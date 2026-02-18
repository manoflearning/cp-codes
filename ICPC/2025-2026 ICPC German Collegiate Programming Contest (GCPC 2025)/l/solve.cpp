#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // TEST
// for (int t = 0; t <= 1440; t++) {
//     cout << "t = " << t << ", ";
    int t; cin >> t;

    if (t <= 60 * 6) {
        cout << 0 << '\n';
    } else if (t <= 9 * 60 + 30) {
        cout << min(t - 6 * 60, 30) << '\n';
    } else if (t <= 10 * 60 + 45) {
        cout << min(t - 9 * 60, 45) << '\n';
    } else {
        cout << t - 10 * 60 << '\n';
    }
// }
}
