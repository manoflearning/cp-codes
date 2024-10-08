#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n;
vector<ll> a;

void init() {}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

ll solve() {
    ll ret = 0;
    for (int i = 0; i + 1 < n; i++) {
        ll diff = 0;
        if (0 <= i - 1 && a[i - 1] < a[i]) diff = a[i] - a[i - 1];
        else if (i + 2 < n && a[i + 1] > a[i + 2]) diff = a[i + 1] - a[i + 2];
        ret += 2 * diff;
        a[i] -= diff, a[i + 1] -= diff;
    }
    return ret;
}

bool isValid() {
    for (int i = 0; i < n; i++) {
        if ((i + 1 < n && a[i] != a[i + 1]) || a[i] < 0) return 0;
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        ll ans = solve();
        reverse(a.begin(), a.end());
        ans += solve();
        cout << (isValid() ? ans : -1) << '\n';
    }
}