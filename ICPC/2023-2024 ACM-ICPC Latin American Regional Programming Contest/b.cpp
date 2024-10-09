#include <bits/stdc++.h>
using namespace std;
int n;
int cnt[202020];

int main(){
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n;
    for(int i=0; i<n*3; i++){
        int input;
        cin >> input;
        cnt[input+101010]++;
    }

    char ans='N';

    for(int i=0; i<202020; i++){
        if(cnt[i]%3){
            ans='Y';
        }
    }

    cout << ans;
    return 0;
}