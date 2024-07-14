#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n; cin >> n;

    map<ll, ll> mp;
    for (ll i = 2; i * i <= n; i++) {
        int x = 0;
        while (n % i == 0) {
            n /= i;
            x++;
        }
        if (x > 0) mp[i] = x;
    }
    if (n > 1) mp[n] = 1;

    ll total_cnt = 1;
    for (auto& i : mp) {
        total_cnt *= (i.sc + 1);
    }

    if (sz(mp) == 1) {
        cout << (total_cnt & 1 ? "N" : "Y");
        return 0;
    }

    cout << (sz(mp) == 2 && total_cnt == 4 ? "Y" : "N");
}