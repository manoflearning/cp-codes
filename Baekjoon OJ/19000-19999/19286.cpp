#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const __float128 EPS = 1e-12;

int n;
ll x[101010], y[101010];
__float128 lambda[101010];

void no() { cout << "No"; exit(0); }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i <= n; i++)
        cin >> x[i] >> y[i];

    __float128 slope_init = (__float128)(y[1] - y[0]) / (x[1] - x[0]);

    __float128 diff1 = slope_init;
    __float128 diff2 = 0;
    for (int i = 1; i + 1 <= n; i++) {
        __float128 slope = (__float128)(y[i + 1] - y[i]) / (x[i + 1] - x[i]);
        if (i + 1 < n) {
            lambda[i] = (slope - (diff1 + diff2)) / 2;
            diff1 += lambda[i];
            diff2 += lambda[i];
        } else {
            lambda[i] = -diff1;
            diff1 += lambda[i];
            diff2 += lambda[i];
            if (abs(diff2 - slope) >= EPS) no();
        }
    }

    __float128 y0 = 0;
    for (int i = 1; i + 1 <= n; i++) {
        y0 += (x[i] - x[0]) * lambda[i];
    }
    if (abs(y[0] - y0) >= EPS) no();

    cout << "Yes";
}
