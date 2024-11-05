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

    int n; cin >> n;

    ll ub = 0;
    vector<ll> a;
    for (int i = 0; i < n; i++) {
        string s; ll x;
        cin >> s >> x;
        if (s == "pig") ub = max(ub, x);
        else a.push_back(x);
    }

    ll ans = ub;
    for (auto x : a) {
        if (x < ub) ans += x;
    }

    cout << ans;
}
