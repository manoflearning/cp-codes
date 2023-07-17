#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll ax, ay, bx, by, k;
        cin >> ax >> ay >> bx >> by >> k;

        if (ax == bx) {
            for (ll y = 1; y <= k; y++) {
                cout << ax + 1 << ' ' << y << '\n';
            }
            continue;
        }

        for (ll x = 1; x <= k; x++) {
            ll yy = (by - ay) * (x - ax) + ay * (bx - ax);
            ll y = (yy + (bx - ax)) / (bx - ax);
            cout << x << ' ' << y << '\n';
        }
    }
}