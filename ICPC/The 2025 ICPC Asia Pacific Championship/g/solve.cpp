#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void sol() {
    ll n,m;
    string s,t;
    cin >> n >> m;
    cin >> s >> t;
    s='*'+s;
    t='*'+t;

    vector<int> zp;

    for(int i=1; i<=m; i++) {
        if(t[i]=='0') zp.push_back(i);
    }

    vector<int> dp(n+1);
    for(int i=1; i<=n; i++) {
        int lp=dp[i-1];

        if(s[i]=='1') {
            dp[i]=lp+(t[lp+1]==s[i]);
        }else {
            int u=upper_bound(all(zp), lp+1)-zp.begin()-1;
            if(u<0) {
                cout << "no\n";
                return;
            }
            dp[i]=zp[u];
        }
    }

    // for(int i=1; i<=n; i++) cout << dp[i] << ' ';

    if(dp[n]==m) cout << "yes\n";
    else cout << "no\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll tc;
    cin >> tc;
    while(tc--) sol();
}
