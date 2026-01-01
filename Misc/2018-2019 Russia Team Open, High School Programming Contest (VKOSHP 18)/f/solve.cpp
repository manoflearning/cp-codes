#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll n;
vector<ll> ans, val;
vector<array<ll,3>> qc;
vector<array<ll,5>> acase;

ll query(ll a, ll b, ll c) {
    cout << "? " << a << ' ' << b << ' ' << c << '\n';
    cout.flush();

    ll res;
    cin >> res;
    return res;
}

void run(ll l, ll r) {
    val.resize(10);
    for(int i=0; i<10; i++) {
        val[i]=query(qc[i][0]+l-1, qc[i][1]+l-1, qc[i][2]+l-1);
    }

    auto v2=val;
    sort(all(v2));

    ll se=v2.back()-v2[0];

    map<ll,ll> s;
    for(int i=3; i<7; i++) {
        s[v2[i]]++;
    }

    ll spe, mid;

    if(sz(s)==1) {
        mid=spe=s.begin()->first;
    }else {
        for(auto &[l,r]:s) {
            // cout << l << ' ' << r << '\n';
            if(r==1) mid=l;
            else spe=l;
        }
    }

    ll ee=spe+se;
    ee/=2;
    ll ss=spe-ee;

    vector<ll> now(6);
    now[1]=ss;
    now[5]=ee;

    ll ft=v2[1]-v2[0];
    ll st=v2[9]-v2[8];

    ll m=mid-ft+st;
    m/=2;

    now[3]=m;

    now[4]=ft+m;
    now[2]=m-st;

    // for(int i=1; i<=5; i++) cout << now[i] << ' ';
    // cout << '\n';

    for(auto &nrr:acase) {
        bool isokay=1;
    
        for(int i=0; i<10; i++) {
            auto &[a,b,c]=qc[i];
            ll aa,bb,cc;
            aa=now[nrr[a-1]];
            bb=now[nrr[b-1]];
            cc=now[nrr[c-1]];

            if(val[i]!=min({aa,bb,cc})+max({aa,bb,cc})) {
                isokay=0;
            }
        }

        if(isokay) {
            for(int i=0; i<5; i++) {
                ans[l+i]=now[nrr[i]];
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    // for(int i=1; i<=5; i++) {
    //     for(int i2=1; i2<=5; i2++) {
    //         if(i==i2) continue;
    //         for(int i3=1; i3<=5; i3++) {
    //             if(i==i3 || i2==i3) continue;
    //             for(int i4=1; i4<=5; i4++) {
    //                 if(i==i4 || i2==i4 || i3==i4) continue;
    //                 for(int i5=1; i5<=5; i5++) {
    //                     if(i==i5 || i2==i5 || i3==i5 || i4==i5) continue;

    //                     acase.push_back({i, i2, i3, i4, i5});
    //                 }
    //             }
    //         }
    //     }
    // }

    array<ll, 5> ord;
    iota(all(ord), 1);
    do {
        acase.push_back(ord);
    } while (next_permutation(all(ord)));

    // for (auto &i : acase) {
    //     for (auto &j : i) cout << j << ' ';
    //     cout << '\n';
    // }
    // cout << endl;

    for(int i=1; i<=5; i++) {
        for(int ii=i+1; ii<=5; ii++) {
            for(int iii=ii+1; iii<=5; iii++) {
                qc.push_back({i, ii, iii});
            }
        }
    }

    cin >> n;
    ans.resize(n+1);

    for(int i=5; i<=n; i+=min(5ll, n-i)) {
        run(i-4, i);
        if(i==n) break;
    }

    cout << "! ";
    for(int i=1; i<=n; i++) cout << ans[i] << ' ';
    cout << '\n';
    cout.flush();

    return 0;
}