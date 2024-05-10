#include <bits/stdc++.h>
using namespace std;

int n, x[1010];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
}

double case1() {
    double l = 0, r = 1e9;
    for (int i = 1; i <= n; i++)
        l = max(l, (double)x[i] / 2); // x[i] <= 2r

    for (int t = 0; t < 60; t++) {
        double mid = (l + r) / 2;
        double res = 0;
        for (int i = 1; i <= n; i++)
            res += asin(x[i] / (2 * mid));
        if (M_PI < res) l = mid;
        else r = mid;
    }

    double res = 0;
    for (int i = 1; i <= n; i++)
        res += asin(x[i] / (2 * l));

    if (abs(res - M_PI) < 1e-7) return l;
    else return 1e9;
}

double case2() {
    int mx_i = 0;
    for (int i = 1; i <= n; i++) {
        if (x[mx_i] < x[i]) mx_i = i;
    }

    double l = (double)x[mx_i] / 2, r = 1e9; // x[i] <= 2r
    for (int t = 0; t < 60; t++) {
        double mid = (l + r) / 2;
        double res1 = asin(x[mx_i] / (2 * mid)), res2 = 0;
        for (int i = 1; i <= n; i++) {
            if (i != mx_i) res2 += asin(x[i] / (2 * mid));
        }
        if (res1 > res2) l = mid;
        else r = mid;
    }

    double res1 = asin(x[mx_i] / (2 * l)), res2 = 0;
    for (int i = 1; i <= n; i++)
        if (i != mx_i) res2 += asin(x[i] / (2 * l));
    
    if (abs(res1 - res2) < 1e-7) return l;
    else return 1e9;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    double ans = case1();
    ans = min(ans, case2());

    cout << fixed;
    cout.precision(8);

    cout << ans;
}