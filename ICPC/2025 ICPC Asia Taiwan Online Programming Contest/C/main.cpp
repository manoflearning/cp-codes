#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m;
ll arr[202020];

void sol() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) arr[i]=0;

    while(m--) {
        ll l,r,v;
        cin >> l >> r >> v;

        ll nl, nr;
        nl=arr[r]+v;
        nr=arr[l]+v;
        arr[l]=nl;
        arr[r]=nr;
    }

    ll ans=0;
    for(int i=1; i<=n; i++) {
        ans=max(ans, arr[i]);
    }

    cout << ans << '\n';
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