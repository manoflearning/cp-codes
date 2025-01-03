#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll f(ll cnt, ll x, ll mod) {
    if (cnt == 1) return x;

    ll res = f(cnt / 2, x, mod);
    return res * res % mod * (cnt & 1 ? x : 1) % mod;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        ll p, a;
        cin >> p >> a;

        if (p == 0 && a == 0) break;

        int bit = 0;
        for (int i = 2; i <= sqrt(p); i++) {
            if (p % i == 0) {
                bit = 1; break;
            }
        }

        if (!bit) {
            cout << "no\n";
            continue;
        }

        ll x = f(p, a, p);
        
        if (x == a) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}