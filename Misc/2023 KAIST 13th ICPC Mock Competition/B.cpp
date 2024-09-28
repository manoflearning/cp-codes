#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll arr[202020], target[202020], n, ans;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> target[i];
    }

    for(int i=1; i<=n; i++){
        if(arr[i]==target[i]) continue;
        ll dis=target[i]-arr[i];
        ans+=abs(dis);
        for(int j=i; j<=n; j+=i){
            arr[j]+=dis;
        }
    }

    cout << ans << '\n';
    return 0;
}
