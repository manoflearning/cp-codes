#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    ll x;
    cin >> n >> k >> x;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    sort(all(a));

    int ans = -1;
    ll acc = 0;
    for (int i = k - 1; i >= 0; i--) {
        acc += a[i];
        if (acc >= x) {
            ans = (k - i) + (n - k);
            break;
        }
    }

    cout << ans << '\n';
}
