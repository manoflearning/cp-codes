#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int inf=1e9+7;
int n, e, cnt[26];
vector<string> srr;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> e;
    srr.resize(n);

    for(auto &s:srr) cin >> s;

    for(int i=0; i<n; i++){
        for(int j=0; j<srr[i].size(); j++){
            if(j==0 || srr[i][j]==srr[i][j-1]) cnt[srr[i][j]-'a']++;
            else break;

            if(srr[i].size()==j+1){
                cnt[srr[i][j]-'a']=inf;
            }
        }
    }

    pair<int, char> mnc(cnt[0], 'a');

    for(int i=1; i<e; i++){
        mnc=min(mnc, {cnt[i], 'a'+i});
    }

    if(mnc.first>=inf){
        cout << "NO";
        return 0;
    }

    for(int i=0; i<=mnc.first; i++) cout << mnc.second;
}
