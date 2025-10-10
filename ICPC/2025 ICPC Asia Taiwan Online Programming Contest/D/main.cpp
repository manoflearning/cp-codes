#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
using namespace std;
typedef long long ll;

ll n;
string s;
ll dp[3030][3030];

void sol() {
    cin >> s;
    n=sz(s);

    for(int i=0; i<n-1; i++) {
        dp[i][i]=0;
        dp[i][i+1]=(s[i]!=s[i+1]);
    }

    dp[n-1][n-1]=0;

    for(int j=2; j<n; j++) {
        for(int i=0; i<n-j; i++) {
            dp[i][i+j]=min(dp[i+1][i+j], dp[i][i+j-1])+1;
            dp[i][i+j]=min(dp[i][i+j], dp[i+1][i+j-1]+(s[i]!=s[i+j]));
        }
    }

    cout << dp[0][n-1] << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        sol();
    }
}