#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mxn=500'000;

struct _seg{
    ll tree[4*mxn];
    ll n;
    void init(ll n_) {
        memset(tree, 0, sizeof(tree));
        n=n_;
    }
    void update(ll p, ll x) {
        update(p,x,0,-1,n);
    }
    void update(ll p, ll x, ll u, ll l, ll r) {
        if(p<l || r<p) return;
        tree[u]+=x;
        if(l==r) return;

        ll m((l+r)>>1);

        update(p,x,u*2+1,l,m);
        update(p,x,u*2+2,m+1,r);
    }
    ll find(ll s, ll e) {
        return find(s,e,0,0,n);
    }
    ll find(ll s, ll e, ll u, ll l, ll r) {
        if(e<l || r<s) return 0;
        if(s<=l && r<=e) return tree[u];

        ll m((l+r)>>1);

        return find(s,e,u*2+1,l,m)+find(s,e,u*2+2,m+1,r);
    }
}seg, seg2;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    vi arr;
    cin >> n;

    arr.resize(n+1,0);

    for(int i=0; i<n; i++) {
        int inp;
        cin >> inp;
        arr[inp]=i;
    }

    seg.init(n-1);
    seg2.init(n);

    int j=1;

    ll sum=0;
    ll ans=1e18;

    // vector<ll> val(1,0);

    for(int i=1; i<=n; i++) {
        while(seg.find(0,arr[i])>1) {
            seg.update(-1,-1);
            seg.update(arr[j],1);
            seg2.update(arr[j]+1, -1);
            seg2.update(n, 1);

            sum-=seg2.find(0, arr[j]);
            // sum-=val[j];
            j++;
        }

        ll nv=seg.find(0,arr[i]);

        // val.push_back(nv);
        sum+=nv;
        seg.update(-1,1);
        seg.update(arr[i],-1);
        seg2.update(arr[i]+1, 1);
        seg2.update(n, -1);
        ans=min(sum+n-(i-j+1), ans);

        // cout << i << ' ' << j << ' ' << sum << '\n';
    }

    cout << ans << '\n';
}
