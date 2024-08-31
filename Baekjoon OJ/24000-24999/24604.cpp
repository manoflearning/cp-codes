#include <bits/stdc++.h>
using namespace std;

int n;
double a[22], b[22];

bool vis[1 << 20];
double dp[1 << 20];

double f(int bit) {
    double& ret = dp[bit];
    if (vis[bit]) return ret;
    int cnt = n;
    for (int i = 0; i < n; i++) {
        if (bit & (1 << i)) cnt--;
    }
    if (cnt == 2) return ret = 0;

    vis[bit] = 1;

    double mul_a = 1.0, mul_b = 1.0;
    for (int i = 0; i < n; i++) {
        if (bit & (1 << i)) continue;
        mul_a *= a[i];
        mul_b *= b[i];
    }

    double p = 0.0;
    for (int i = 0; i < n; i++) {
        if (bit & (1 << i)) continue;
        p += (mul_a / a[i]) * b[i];
        p += (mul_b / b[i]) * a[i];
    }

    ret += 1 / p;

    for (int i = 0; i < n; i++) {
        if (bit & (1 << i)) continue;
        ret += (mul_a / a[i]) * b[i] / p * f(bit | (1 << i));
        ret += (mul_b / b[i]) * a[i] / p * f(bit | (1 << i));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = 1.0 - a[i];
    }

    cout << fixed;
    cout.precision(8);
    cout << f(0);
}