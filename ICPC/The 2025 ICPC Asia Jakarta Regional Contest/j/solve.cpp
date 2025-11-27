#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

ll n,a,b;

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
    // #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> a >> b;

    __int128_t nn=n, one=1;

    nn<<=1;

    for(int i=0; i<64; i++) {
        if((nn&(one<<i))==0 && (nn&(one<<(i+1))) && (nn&(one<<(i+2)))==0 && (nn&(one<<(i+3)))) {
            cout << "NO\n";
            return 0;
        }
    }

    ll mn=min(a,b);
    a-=mn;
    b-=mn;

    if(a>64 || b>64) {
        cout << "NO\n";
        return 0;
    }

    nn=n;
    nn<<=1;

    ll cnt=0;

    for(int i=0; i<127; i++) {
        if((nn&(one<<i)) != (nn&(one<<(i+1)))) {
            cnt++;
        }
    }

    nn=n;

    for(int i=0; i<a; i++) {
        nn|=nn*2;
    }
    for(int j=0; j<b; j++) {
        nn&=nn*2;
    }

    nn<<=1;

    ll cnt2=0;

    for(int i=0; i<127; i++) {
        if((nn&(one<<i)) != (nn&(one<<(i+1)))) {
            cnt2++;
        }
    }

    if(cnt==cnt2) cout << "YES\n";
    else cout << "NO\n";
}