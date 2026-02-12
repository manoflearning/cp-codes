#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using pll = pair<ll,ll>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<pll> arr(n);
    for(auto &[l,r]:arr) cin >> l >> r;

    ll last = arr.back().second;
    reverse(all(arr));
    arr.push_back({0,0});

    vector<pll> ans;
    for(int i = 0; i < n; i++) {
        auto &[l,r] = arr[i];
        ll need = (last - l + 1)/2;
        ll bf = l - need;

        // cout << bf << '\n';

        if(bf < 0) {
            cout << "impossible\n";
            return 0;
        }

        if(bf < arr[i+1].second) continue;

        if(bf == arr[i+1].second+1) {
            bf--;
            if(((last - l) & 1) == 0) need++;
        }
        
        last = arr[i+1].second;

        ans.push_back({bf, bf+need});

        if(bf != arr[i+1].second) {
            ll dis = bf - arr[i+1].second;
            ans.push_back({arr[i+1].second, arr[i+1].second + dis / 2});
        }
    }

    reverse(all(ans));

    cout << sz(ans) << '\n';
    for(auto &[l,r]:ans) cout << l << ' ' << r << '\n';
}
