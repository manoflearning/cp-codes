#include <bits/stdc++.h>
using namespace std;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const __float128 PI = 3.14159265358979323846264338327950288;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int deg, n;
    cin >> deg >> n;

    vector<pair<__float128, __float128>> a;
    for (int i = 0; i < n; i++) {
        int x, h;
        cin >> x >> h;
        __float128 y = x + h / tan(deg / (double)180 * (double)PI);
        a.push_back({x, y});
    }

    sort(all(a), [](const pair<__float128, __float128> &p1, const pair<__float128, __float128> &p2) {
        return p1.sc < p2.sc;
    });

    __float128 ans = 0;
    __float128 prv = 0;
    for (auto [l, r] : a) {
        if (prv > l) l = prv;

        ans += max<__float128>(0, r - l);
        prv = max(prv, r);
    }

    cout << fixed;
    cout.precision(8);
    cout << (double)ans;
}
