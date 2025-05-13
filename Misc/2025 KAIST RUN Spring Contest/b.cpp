#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int n;
    ll m;
    cin >> n >> m;

    vector<ll> a;
    int cnt0 = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        if (x == 0) cnt0++;
        else a.push_back(x);
    }

    ll ans = 0;

    sort(all(a));

    ll suma = 0, cnta = 0;
    for (auto &i : a) {
        ans += cnta * i - suma;
        suma += i, cnta++;
    }

    while (cnt0 > 0) {
        if (cnta * m - suma > suma - cnta * 1) {
            ans += cnta * m - suma;
            suma += m;
            cnta++;
        } else {
            ans += suma - cnta * 1;
            suma += 1;
            cnta++;
        }
        cnt0--;
    }

    cout << ans;
}
