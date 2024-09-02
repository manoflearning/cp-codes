#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll x, y, z;
        cin >> x >> y >> z;

        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);

        ll ans = 0;
        if (y - x > 1) {
            ll diff = y - x;
            x += diff / 2;
            y -= diff / 2;
            z -= diff / 2;
            ans += diff / 2;
        }
        if (z - y > 0) {
            ll diff = (z - y) / 2 * 2;
            z -= diff;
            ans += diff;
        }

        {
            ll mn = min({ x, y, z }) - 1;
            x -= mn;
            y -= mn;
            z -= mn;
            ans += 3 * mn;
        }
        {
            if (y == 1 && z == 1) ans += 1;
            else if (y == 1 && z == 2) ans += 3;
            else if (y == 2 && z == 2) ans += 4;
            else if (y == 2 && z == 3) ans += 5;
            else assert(0);
        }

        cout << (ans & 1 ? "B" : "R") << '\n';
    }
}
