#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int dx[] = {1, -1, 0, 0};
constexpr int dy[] = {0, 0, 1, -1};

ll n,m;
vector<vector<ll>> arr;
ll nd, sh;

set<ll> get_val(ll y, ll x) {
    set<ll> ret;
    for(int i=1; i<=4; i++) {
        ret.insert(i);
    }

    for(int i=0; i<4; i++) {
        ll ny, nx;
        ny=y+dy[i];
        nx=x+dx[i];
        if(ny<0 || nx<0 || ny>=n || nx>=m) continue;

        if(ret.count(arr[ny][nx])) ret.erase(arr[ny][nx]);
    }

    return ret;
}

ll get_val2(ll y, ll x) {
    auto res=get_val(y,x);

    if(~sh) {
        if(res.count(sh)) return sh;
    }

    for(ll i=1; i<=4; i++){
        if(!res.count(i)) continue;
        if(nd==i) continue;

        return i;
    }
}

bool isokay(ll y, ll x) {
    for(int i=0; i<4; i++) {
        ll ny, nx;
        ny=y+dy[i];
        nx=x+dx[i];
        if(ny<0 || nx<0 || ny>=n || nx>=m) continue;

        if(arr[ny][nx]==arr[y][x]) return 0;
    }

    return 1;
}

void sol() {
    nd=-1;
    sh=-1;
    cin >> n >> m;

    arr.resize(n);
    for(auto &v:arr) {
        v.resize(m);
        for(auto &a:v) cin >> a;
    }

    for(int i=0; i<m; i++) {
        if(arr[0][i]==0) {
            arr[0][i]=get_val2(0,i);
        }

        if(arr[n-1][i]==0) {
            arr[n-1][i]=get_val2(n-1, i);
        }
    }

    for(int i=0; i<n; i++) {
        if(arr[i][0]==0) {
            arr[i][0]=get_val2(i,0);
        }

        if(arr[i][m-1]==0) {
            arr[i][m-1]=get_val2(i,m-1);
        }
    }

    ll mn=3;

    ll nn, mm;
    nn=n;
    mm=m;

    while(mn<nn) {
        nn--;
        for(int i=1; i<m-1; i++) {
            arr[nn-1][i]=get_val2(nn-1, i);
        }
    }
    while(mn<mm) {
        mm--;
        for(int i=1; i<n-1; i++) {
            arr[i][mm-1]=get_val2(i, mm-1);
        }
    }

    // {
    //     ll y1, y2, x1, x2;
    //     y1=1;
    //     y2=mn-2;

    //     x1=1;
    //     x2=mn-2;

    //     ll sd=-1;
    //     auto a=get_val(y1, x1);
    //     auto b=get_val(y2, x2);

    //     for(int i=1; i<=4; i++) {
    //         if(a.count(i) && b.count(i)) {
    //             sd=i;
    //             break;
    //         }
    //     }

    //     if(sd==-1) {
    //         arr[y1][x1]=*a.begin();
    //         nd=*a.begin();
    //         sh=*a.rbegin();

    //         for(int i=y2; i>y1; i--) {
    //             arr[i][x1]=get_val2(i, x1);
    //         }

    //         for(int i=x2; i>x1; i--) {
    //             arr[y1][i]=get_val2(y1, i);
    //         }

    //         if(arr[y1][x1+1]!=arr[y1+1][x1] && b.count(arr[y1][x1+1]) && b.count(arr[y1+1][x1])) {
    //             arr[y1][x1]=*a.rbegin();
    //             arr[y1][x1+1]=arr[y1+1][x1]=*a.begin();
    //         }
            
    //         sd=*b.begin();
    //         if((*b.begin())==(arr[y1][x1+1]) || (*b.begin())==(arr[y1+1][x1])) sd=*b.rbegin();
    //         sh=-1;

    //         y1++;
    //         x1++;
    //     }

    //     arr[y1][x1]=arr[y2][x2]=sd;
    //     nd=sd;

    //     for(int i=y2; i>y1; i--) {
    //         arr[i][x1]=get_val2(i, x1);
    //     }

    //     for(int i=x2; i>x1; i--) {
    //         arr[y1][i]=get_val2(y1, i);
    //     }

    //     for(int i=y1; i<y2; i++) {
    //         arr[i][x2]=get_val2(i, x2);
    //     }
    //     for(int i=x1; i<x2; i++) {
    //         arr[y2][i]=get_val2(y2, i);
    //     }

    //     nd=-1;

    //     y1++;
    //     y2--;
    //     x1++;
    //     x2--;

    //     for(int i=y1; i<=y2; i++) {
    //         for(int j=x1; j<=x2; j++) {
    //             if((i+j)&1) arr[i][j]=sd;
    //         }
    //     }
    // }

    // for(int i=0; i<n; i++) {
    //     for(int j=0; j<m; j++) {
    //         if(arr[i][j]) continue;

    //         arr[i][j]=get_val2(i,j);
    //     }
    // }

    for(int a=1; a<=4; a++) {
        for(int b=1; b<=4; b++) {
            for(int c=1; c<=4; c++) {
                for(int d=1; d<=4; d++) {
                    arr[1][1]=a;
                    arr[1][2]=b;
                    arr[2][1]=c;
                    arr[2][2]=d;

                    if(isokay(1,2) && isokay(1,1) && isokay(2,2) && isokay(2,1)) {
                        for(auto &v:arr) {
                            for(auto &a:v) cout << a << ' ';
                            cout << '\n';
                        }

                        return;
                    }
                }
            }
        }
    }

}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        sol();
    }
}
