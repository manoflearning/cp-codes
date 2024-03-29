#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll mul(ll x, ll y, ll mod) {
    if (y == 0) return 1;
    __int128_t res = mul(x, y >> 1, mod);
    __int128_t ret = res * res % mod * (y & 1 ? x : 1) % mod;
    return (ll)ret;
}
ll gcd(ll x, ll y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}
int validation(ll ans1, ll ans2) {
    for (int i = 2; i <= 500; i++) {
        if (mul(i, ans1 - 1, ans1) != 1) return 0;
    }
    return ans1 % ans2 == 0;
}
ll getFactor(ll x) {
    for (ll i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) return i;
    }
    return 1;
}

void naiveBruteforce() {
    for (ll x = 501; x <= 100'000'000; x++) {
        // if x is prime, x cannot be the answer
        int isPrime = 1;
        ll pf = -1;
        for (ll i = 2; i <= sqrt(x); i++) {
            if (x % i == 0) { isPrime = 0; pf = i; break; }
        }
        if (isPrime) continue;

        // check if x can be the answer
        int isPass = 1;
        for (int i = 2; i <= 500; i++) {
            if (mul(i, x - 1, x) != 1) { isPass = 0; break; }
        }
        if (isPass) {
            cout << x << ' ' << pf;
            break;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    //naiveBruteforce();

    ll ans1 = 172018713961ll;
    ll ans2 = getFactor(172018713961ll);

    assert(501 <= ans1 && ans1 <= (ll)1e15);
    assert(1 < ans2 && ans2 < ans1);
    assert(validation(ans1, ans2));
    
    cout << ans1 << ' ' << ans2 << '\n';
}