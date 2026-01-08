#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()

ll n,l;
vector<pll> arr;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> l;
    arr.resize(n);
    for(auto &[x,y]:arr) cin >> y >> x;

    if(n&1) {
        cout << "no" << '\n';
        return 0;
    }

    sort(all(arr));

    ll s[3]{0};

    ll ans=0;

    for(auto &[y,x]:arr) {
        if((s[1]&1)==(s[2]&1) && s[1]<y && s[2]<y) {
            s[1]=y-1;
            s[2]=y-1;
            s[x]=y;
        }
        else {
            ll dis=y-s[x]-1;
    
            if(dis&1) {
                ans++;
                s[x]=y-1;
            }
            else {
                s[x]=y;
            }
        }
    }

    cout << ans << '\n';
}