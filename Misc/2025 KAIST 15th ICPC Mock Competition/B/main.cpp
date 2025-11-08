#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll tc;
string s;
ll dp[101010][2];

void sol() {
    cin >> s;
    ll n=sz(s);

    s='*'+s;
    for(int i=1; i<=n; i++) {
        dp[i][0]=dp[i-1][1]+1;
        if(s[i]!=s[i-1]) dp[i][0]=max(dp[i-1][0]+1, dp[i][0]);
        
        if(i>=2) dp[i][1]=dp[i-2][0]+1;
    }

    cout << max(dp[n][0], dp[n][1]) << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> tc;
    while(tc--) sol();
}
