#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()

ll t, n, a, b, k;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> t >> n >> a >> b >> k;

    if(n<k) {
        cout << 0 << '\n';
        return 0;
    }

    ll aa, bb;
    aa=(n+1)/2;
    bb=n/2;

    if(a<b) {
        swap(aa, bb);
        swap(a,b);
    }

    if(aa>=k) {
        ll ans=(aa*a+bb*b)/k;
        cout << min(ans, t) << '\n';
    }
    else {
        ll rem=k-aa;

        ll rt=(bb*b)/rem;

        if(a<rt) {
            cout << min(t,(aa*a+bb*b)/k) << '\n';
        }else cout << min(rt,t) << '\n';
    }

    return 0;
}