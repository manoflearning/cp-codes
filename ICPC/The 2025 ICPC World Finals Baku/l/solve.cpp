#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    ll xc, yc, xa, ya;
    cin >> n >> xc >> yc >> xa >> ya;

    vector<pii> arr;

    rep(i, 0, n) {
        int x1, y1, x2, y2;

        cin >> x1 >> y1 >> x2 >> y2;
        arr.push_back({y1, y2});
    }

    arr.push_back({yc, yc});

    sort(all(arr));

    if(yc<=ya) {
        cout << 0 << '\n';
        return 0;
    }

    ll last=ya;
    ll ans=0;
    for(auto &[l,r]:arr) {
        if(l>yc) break;
    
        if(last>=l) last=max((ll)r, last);
        else {
            ans+=l-last;
            last=max((ll)r, last);
        }
    }

    cout << ans << '\n';
}