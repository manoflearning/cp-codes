#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

ll r, c, l;
ll ans;

ll f(ll x) {
    ll ret = 0;
    for (ll i = 1; i < x; i++) {
        ll p2 = x * x - i * i;

        ll s = 0, e = INF;
        while (s < e) {
            ll mid = (s + e + 1) >> 1;
            if (mid * mid > p2) e = mid - 1;
            else s = mid;
        }

        ret += s;
    }
    return ret;
}

vector<ll> f2(ll x, ll lb) {
    vector<ll> ret;
    for (ll i = lb; i < x; i++) {
        ll p2 = x * x - i * i;

        ll s = 0, e = INF;
        while (s < e) {
            ll mid = (s + e + 1) >> 1;
            if (mid * mid > p2) e = mid - 1;
            else s = mid;
        }

        ret.push_back(s);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin >> r >> c >> l;

    ans += max(0ll, l - r);
    ans += max(0ll, l - c);
    ans += 2 * l;

    ans += 3 * f(l);

    if (l > r) ans += f(l - r);
    if (l > c) ans += f(l - c);
    if (l > r + c) {
        vector<ll> res1 = f2(l - r, c + 1);
        vector<ll> res2 = f2(l - c, r + 1);
        
        for (int i = 0; i < sz(res1); i++) {
            int x1 = res1[i], y1 = i + 1;
            
            int s = 0, e = sz(res2) - 1;
            while (s < e) {
                int mid = (s + e + 1) >> 1;
                
                int x2 = mid + 1, y2 = res2[mid];
                if (x2 <= x1 && y1 <= y2) s = mid;
                else e = mid - 1;
            }

            ans -= s + 1;
            
            /*for (int j = 0; j < sz(res2); j++) {
                int x2 = j + 1, y2 = res2[j];
                if (x2 <= x1 && y1 <= y2) ans--;
            }*/
        }
    }
    
    cout << ans;

    return 0;
}