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

    int n; cin >> n;

    ll ans = 0;
    array<ll, 5> point = {0, 760, 1900, 5700, 22800};
    int now = 0, prv = 0, level = 18;
    for (int i = 0; i < n; i++) {
        string log; cin >> log;

        if (log == "single") {
            now += 1;
            ans += point[1];
        } else if (log == "double") {
            now += 2;
            ans += point[2];
        } else if (log == "triple") {
            now += 3;
            ans += point[3];
        } else if (log == "tetris") {
            now += 4;
            ans += point[4];
        }

        if (now >= 130 && now / 10 != prv / 10) {
            point[1] += 40;
            point[2] += 100;
            point[3] += 300;
            point[4] += 1200;
            prv = now;
            level++;
        }
    }

    cout << ans << ' ' << level << '\n';
}
