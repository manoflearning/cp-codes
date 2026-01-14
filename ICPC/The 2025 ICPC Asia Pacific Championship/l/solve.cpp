#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int dy[4]{0,0,1,-1}, dx[4]{1,-1,0,0};

int r, c, n, p;
vector<vi> arr;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> r >> c >> n >> p;

    arr.resize(r);
    for(auto &v:arr) {
        v.resize(c);
        for(auto &a:v) cin >> a;
    }

    set<int> s;

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(arr[i][j]>p || arr[i][j]==0) continue;

            int ny, nx;
            for(int d=0; d<4; d++) {
                ny=i+dy[d];
                nx=j+dx[d];

                if(ny<0 || nx<0 || ny>=r || nx>=c) continue;

                if(arr[ny][nx]==0) continue;

                int nv=arr[ny][nx]-arr[i][j]+p;
                if(nv<1 || nv>n) continue;

                s.insert(nv);
            }
        }
    }

    cout << sz(s) << "/" << n-1 << '\n';
}
