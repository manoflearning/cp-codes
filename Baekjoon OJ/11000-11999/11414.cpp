#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll lcm(ll x, ll y) {
    return x * y / gcd(x, y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll A, B;
    cin >> A >> B;
    if (A > B) swap(A, B); // wlog, A <= B

    if (A == B) {
        cout << 1;
        return 0;
    }

    ll diff = B - A; // invariant
    // diff >= gcd(A + N, B + N)

    ll mn = lcm(A + diff, B + diff), ans = diff;
    for (ll N = 1; N < diff && B + N < mn; N++) {
        ll res = lcm(A + N, B + N);
        if (res < mn) {
            mn = res;
            ans = N;
        }
    }

    cout << ans;
}