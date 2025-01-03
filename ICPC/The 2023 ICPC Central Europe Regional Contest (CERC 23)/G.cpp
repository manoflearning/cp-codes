#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const long double PI = 3.14159265358979323846264338327950288;

ll xa, ya, xb, yb, xc, yc, r;

void init() {}

void input() {
    cin >> xa >> ya >> xb >> yb >> xc >> yc >> r;
}

long double cal(long double theta) {
    long double xd = xc + r * sin(theta);
    long double yd = yc + r * cos(theta);
    return sqrt(pow(xa - xd, 2) + pow(ya - yd, 2)) 
    + sqrt(pow(xb - xd, 2) + pow(yb - yd, 2));
}

long double dist(ll x, ll y, ll p, ll q) {
    return sqrt(pow(x - p, 2) + pow(y - q, 2));
}

long double ts(long double l, long double r) {
    for (int i = 0; i < 60; i++) {
        long double mid1 = (2 * l + r) / 3;
        long double mid2 = (l + 2 * r) / 3;

        if (cal(mid1) <= cal(mid2)) r = mid2;
        else l = mid1;
    }
    return cal(l);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cout << fixed;
    cout.precision(8);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (dist(xa, ya, xc, yc) <= r || dist(xb, yb, xc, yc) <= r) {
            cout << dist(xa, ya, xb, yb) << '\n';
        }
        else {
            long double ans = 1e18;
        
            ans = min(ans, ts(0, PI));
            ans = min(ans, ts(PI / 2, PI + PI / 2));
            ans = min(ans, ts(PI, 2 * PI));
            ans = min(ans, ts(PI + PI / 2, 2 * PI + PI / 2));

            cout << ans << '\n';
        }
    }
}