#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll N, K, P;

ll fac(ll x) {
    ll ret = 1;
    for (ll i = 2; i <= x; i++) ret *= i;
    return ret;
}
ll powxy(ll x, ll y) { 
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = powxy(x, y / 2);
    return res * res % P * (y & 1 ? x : 1) % P;
}
ll fac(ll x, ll mod) {
    ll ret = 1;
    for (ll i = 2; i <= x; i++) {
        ret = ret * i % mod;
    }
    return ret;
}

void print(ll x) { cout << x; exit(0); }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin >> N >> K >> P;

    if (N >= P) print(0);
    // 2 <= N <= P - 1, K >= 2
    if (N == 2) print(2);
    // 3 <= N <= P - 1, K >= 2
    if (N == 3) {
        if (K == 2) print(720 % P);
        else N = 6, K--;
    }
    // 4 <= N <= P - 1, K >= 2
    if (N >= 13) print(0); // 13! = 6'227'020'800 > P
    // 4 <= N <= 12, K >= 2
    if (K >= 3) print(0); // 4!!! > P
    // 4 <= N <= 12, K = 2
    ll x = fac(N);
    if (P <= x) print(0);
    // 4 <= N <= 12, K = 2, N! <= P - 1
    if (N <= 11) print(fac(x, P));
    // N = 12, K = 2, N! <= P - 1
    if (N == 12) {
        ll rFac = 1;
        for (ll i = x + 1; i < P; i++)
            rFac = rFac * i % P;
        ll ans = (P - 1) * powxy(rFac, P - 2) % P;
        print(ans);
    }
}