#include <bits/stdc++.h>
using namespace std;
#define ll long long

int K;
vector<pair<ll, ll>> qs;

ll f(ll x) {
    ll ret = x;
    for (auto [q, cnt] : qs) {
        if (x < q * q) break;
        if (cnt & 1) ret -= x / (q * q);
        else ret += x / (q * q);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // initialize
    for (ll i = 2; i <= sqrt(2e9); i++) {
        ll x = i;
        int bit = 1, cnt2 = 0;
        for (ll j = 2; j <= sqrt(x); j++) {
            int cnt = 0;
            while (x % j == 0) x /= j, cnt++;
            if (cnt >= 2) { bit = 0; break; }
            if (cnt) cnt2++;
        }
        if (x > 1) cnt2++;
        if (bit) qs.push_back({ i, cnt2 });
    }

    // solve
    cin >> K;

    ll l = 1, r = 2 * K;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (f(mid) < K) l = mid + 1;
        else r = mid;
    }

    cout << l;
}