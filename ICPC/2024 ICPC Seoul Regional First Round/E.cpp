#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, m;
ll a[1010][1010], b[1010][1010];
vector<ll> dp(1010, -INF);
// int M[1010], _min[1010];

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n >> m;
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) cin >> a[i][j];
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) cin >> b[i][j];

    for(int x=1; x<=n; x++){
        for (int y = 1; y <= n; y++) {
            dp[x] = max(dp[x], abs(a[y][x] - b[y][x]));
        }
    }

    ll ans=0;

    for(int i=0; i<m; i++){
        int x; cin >> x;
        ans+=dp[x];
    }

    cout << ans;

    return 0;
}