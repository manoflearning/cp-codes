#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

__int128_t gcd(__int128_t x, __int128_t y) {
    if (!y) return x;
    return gcd(y, x % y);
}

__int128_t a, b, c, d;

void input() {
    ll aa, bb, cc, dd;
    cin >> aa >> bb >> cc >> dd;
    a = aa, b = bb, c = cc, d = dd;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        __int128_t l = 1, r = 1e20;
        while (l < r) {
            __int128_t mid = (l + r) / 2;

            __int128_t res1 = b * mid / a + 1;
            __int128_t res2 = d * mid / c + 1;
            if (res1 - res2 > 0) r = mid;
            else l = mid + 1;
        }

        cout << (ll)(b * l / a + 1) << '\n';
    }
}
