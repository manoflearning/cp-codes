#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll R, n; cin >> R >> n;
    vl arr(n); for(auto &a:arr) cin >> a;

    ll l = 0, r = R;

    for(auto &a:arr) {
        l = min(max(0ll, l + a), R);
        r = min(max(0ll, r + a), R);
    }

    if(l == r) cout << l << '\n';
    else cout << "uncertain\n";
}
