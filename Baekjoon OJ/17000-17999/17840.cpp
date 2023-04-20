#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int q, MOD;
vector<ll> a, b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> q >> MOD;
    a.push_back(1);
    a.push_back(1);
    a.push_back(2 % MOD);
    while (a[sz(a) - 2] != 1 || a[sz(a) - 1] != 1) {
        a.push_back((a[sz(a) - 2] + a[sz(a) - 1]) % MOD);
    }
    a.pop_back();
    a.pop_back();

    for (auto& x : a) {
        string s = to_string(x);
        for (auto& c : s)
            b.push_back(c - '0');
    }
    
    while (q--) {
        ll n; cin >> n;
        cout << b[(n - 1) % sz(b)] << '\n';
    }
}