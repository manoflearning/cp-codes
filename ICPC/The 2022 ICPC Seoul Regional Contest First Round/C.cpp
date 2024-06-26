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

    int n; cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    for (auto& i : a) {
        cin >> i;
        sum += i;
    }

    sort(a.begin(), a.end());

    ll av = sum / n, one = n - sum % n;
    
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i < one) ans += abs(a[i] - av);
        else ans += abs(a[i] - av - 1);
    }
    
    cout << ans / 2;

    return 0;
}