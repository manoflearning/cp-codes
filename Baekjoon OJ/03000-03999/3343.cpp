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

    ll n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;

    if (b * c > d * a) {
        swap(a, c); swap(b, d);
    }

    ll ans = 1e18;
    for (int i = 0; i < a; i++) {
        ll res = i * d + max(0ll, (n - i * c + a - 1) / a) * b;
        
        ans = min(ans, res);
    }

    cout << (ll)ans;

    return 0;
}