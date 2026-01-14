#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int type(ll m) {
    cout << "type " << m << '\n';
    cout.flush();
    
    string res;
    cin >> res;
    return res=="lily";
}

ll multi(ll m) {

    cout << "multi " << m << '\n';
    cout.flush();
    
    ll res;
    cin >> res;
    return res;
}

void sol() {
    ll n;
    cin >> n;

    ll r=0, l=n+1;

    while(r+1<l) {
        ll m((l+r)>>1);

        if(type(m)) {
            l=m;
        }else r=m;
    }

    ll res, res2;
    if((l!=n+1) && (res=multi(l))) {
        res2=multi(l-1);

        ll rc=abs(res-res2);
        ll lc=res/rc;

        cout << "answer " << l-lc+rc << '\n';
    }else {
        if((r!=0) && (res=multi(r-1))) {
            res2=multi(r);

            ll lc=abs(res-res2);
            ll rc=res2/lc;

            cout << "answer " << r-lc+rc << '\n';
        }
        else {
            cout << "answer " << r << '\n';
        }
    }

    cout.flush();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll tc;
    cin >> tc;
    while(tc--) sol();
}
