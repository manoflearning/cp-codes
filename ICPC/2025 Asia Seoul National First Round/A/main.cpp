#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll n,ans;
vector<pll> arr;
vector<ll> brr;
bool vis[3030];

void bfs(ll i) {
    queue<ll> q;
    q.push(i);

    while(sz(q)) {
        auto u=q.front(); q.pop();

        vis[u]=1;
        if(u+1<n && !vis[u+1] && brr[u+1]>brr[i]) q.push(u+1);
        if(u-1>=0 && !vis[u-1] && brr[u-1]>brr[i]) q.push(u-1);
    }
}

int main(int argc, char * argv[]){
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    arr.resize(n);
    brr.resize(n);

    for(int i=0; i<n; i++) {
        cin >> arr[i].first;
        arr[i].second=i;
    }
    for(auto &b:brr) cin >> b;

    sort(all(arr));
    for(auto &[_,i]:arr) {
        if(vis[i]) continue;
        ans++;
        bfs(i);
    }

    cout << ans << '\n';

    return 0;
}