// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int n;
vector<double> a;

void init() {}

void input() {
    cin >> n;
    a.resize(n + 2);
    a[0] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[n + 1] = 1;
}

double unit(int idx) {
    return (double)(idx != 0 && idx != n + 1) / n;
}

double solve() {
    double ret = 0;
    for (int i = 1; i + 1 <= n; i++) {
        ret = max(ret, a[i + 1] - a[i]);
    }

    double mn = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        mn += unit(i);
        mx += unit(i);

        mn = min(mn, unit(i) + a[i]);
        mn = min(mn, unit(i) + a[i - 1]);
        mx = max(mx, unit(i) + a[i]);
        mx = max(mx, unit(i) + a[i - 1]);

        ret = max(ret, -(mn - a[i]));
        ret = max(ret, -(mn - a[i + 1]));

        ret = max(ret, mx - a[i]);
        ret = max(ret, mx - a[i + 1]);

        // for (int j = i; j <= n; j++) {
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j] - a[i])));
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j + 1] - a[i])));
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j] - a[i - 1])));
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j + 1] - a[i - 1])));
        // }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        sort(all(a));

        cout << fixed;
        cout.precision(10);
        cout << solve() << '\n';

        cout << flush;
    }
}