#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n; cin >> n;

    set<ll> vis;

    ll x = (__int128_t)n * (n + 1) / 2 % n;
    
}

// n = 2: 0-1(-1-0-0-1-...)
// n = 3: 0-1(-0-0-1-0-0-1-0)
// n = 4: 0-1-3-2
// n = 5: 0-1-3(-1-0)
// n = 6: 0-1-3-0-4-3-3-4-

// n = 2: 0-1-3-6-10-...
// n = 3: 0-1-3-6-10-...