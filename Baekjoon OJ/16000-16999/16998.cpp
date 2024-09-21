#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

ll f(ll p, ll q, ll n) {
    if (!p) return 0;

    if (p >= q) return n * (n + 1) / 2 * (p / q) + f(p % q, q, n);
    else return n * (p * n / q) + (n / q) - f(q, p, p * n / q);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int w; cin >> w;
    while (w--) {
        ll p, q, n;
        cin >> p >> q >> n;
        ll g = gcd(p, q);
        cout << p * n * (n + 1) / 2 - q * f(p / g, q / g, n) << '\n';
    }
}
