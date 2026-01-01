#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pll pair<ll,ll>

ll n,m;

struct pr{
    ll len, i;
    vector<ll> arr;

    bool operator<(const pr &tar) const {
        return len<tar.len;
    }
};

vector<pr> arr;
vector<ll> ts, rem;
set<pll> s;
vector<tuple<ll,ll,ll>> ans;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    arr.resize(n);
    rem.resize(n,0);
    ts.resize(n);

    ll sum=0;

    for(int i=0; i<n; i++) {
        auto &[len, ii, brr]=arr[i];

        cin >> len;
        brr.resize(len+1);
        brr[0]=-1e18;
        for(int i=1; i<=len; i++) cin >> brr[i];
        sort(all(brr));

        ii=i;

        sum+=len;
    }

    ll mts=sum/n;
    for(auto &a:ts) a=mts;
    for(int i=0; i<sum%n; i++) {
        ts[i]++;
    }

    sort(all(arr));
    reverse(all(arr));

    for(int i=0; i<n; i++) {
        if(ts[i]<arr[i].len) {
            rem[i]=arr[i].len-ts[i];

            for(auto &a:arr[i].arr) {
                s.insert({a, i});
            }
        }
        else {
            ll nl=arr[i].len;
            // while(sz(s) && rem[s.begin()->second]==0) s.erase(s.begin());
    
            // while(sz(s) && nl<ts[i] && ((arr[i].arr).empty() || s.begin()->first<arr[i].arr[0])) {
            //     ans.push_back({arr[s.begin()->second].i+1, arr[i].i+1, s.begin()->first});
            //     rem[s.begin()->second]--;
            //     s.erase(s.begin());

            //     nl++;
            //     while(sz(s) && rem[s.begin()->second]==0) s.erase(s.begin());
            // }

            for(int j=0; j<=arr[i].len; j++) {
                auto x=arr[i].arr[j];
            
                auto ub=s.upper_bound({x,i});

                while(ub!=s.end() && rem[ub->second]==0) {
                    s.erase(ub);
                    ub=s.upper_bound({x,i});
                }

                while(ub!=s.end() && nl<ts[i] && (j==arr[i].len || ub->first<arr[i].arr[j+1])) {
                    ans.push_back({arr[ub->second].i+1, arr[i].i+1, ub->first});
                    x=ub->first;
                    rem[ub->second]--;
                    nl++;

                    s.erase(ub);
                    ub=s.upper_bound({x,i});

                    while(ub!=s.end() && rem[ub->second]==0) {
                        s.erase(ub);
                        ub=s.upper_bound({x,i});
                    }
                }
            }
        }
    }

    cout << sz(ans) << '\n';
    for(auto &[a,b,c]:ans) {
        cout << a << ' ' << b << ' ' << c << '\n';
    }

    return 0;
}