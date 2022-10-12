#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, k, x;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    
    if (k < n) {
        cout << 0;
        return 0;
    }

    x = k;
    for (ll i = 1; ; i *= 10) {
        if (x * n / i == 0) {
            cout << 0;
            return 0;
        }

        ll z = x * n / i % 10;
        if (z == k) break;
        x += z * i * 10;
    }

    cout << x;

    return 0;
}