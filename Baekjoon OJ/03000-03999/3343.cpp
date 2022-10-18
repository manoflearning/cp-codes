#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;

    if (b * c > d * a || (b * c == d * a && a > c)) {
        swap(a, c); swap(b, d);
    }

    ll lc = lcm(a, c);

    ll p = n / lc, q = n % lc;

    ll ans = p * (lc / a) * b, ans2 = (q + c - 1) / c * d;
    
    for (ll l = 0; (l - 1) * a <= q; l++) {
        ll r = max(0ll, q - l * a + c - 1) / c;
        
        ans2 = min(ans2, l * b + r * d);
    }
    
    cout << ans + ans2;

    return 0;
}