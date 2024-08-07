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

    if (A == B) {
        cout << 1;
        return 0;
    }

    if (A > B) swap(A, B); // wlog, A <= B

    ll diff = B - A;
    vector<ll> div;
    for (ll i = 1; i * i <= diff; i++) {
        if (diff % i == 0) {
            div.push_back(i);
            if (i != diff / i) 
                div.push_back(diff / i);
        }
    }

    ll mn = 2e18, ans = 1e18;
    for (auto& i : div) {
        ll N = i - A % i;
        ll res = lcm(A + N, B + N);
        if (res < mn || (res == mn && N < ans)) {
            mn = res, ans = N;
        }
    }

    cout << ans;
}