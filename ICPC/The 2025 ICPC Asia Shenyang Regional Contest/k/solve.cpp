#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll n,s; cin >> n >> s;
    vector<array<ll,4>> arr(n);

    ll pxs=0, pys=0, qxs=0, qys=0;
    for(auto &[px, py, qx, qy]:arr) {
        cin >> px >> py >> qx >> qy;
        pxs+=px;
        pys+=py;
        qxs+=qx;
        qys+=qy;
    }

    s--;
    pxs-=arr[s][0]*2;
    pys-=arr[s][1]*2;

    for(int i = 0; i < n; i++) {
        auto &[px, py, qx, qy]=arr[i];
        ll nqxs, nqys;
        nqxs=qxs-2*qx;
        nqys=qys-2*qy;

        if(pxs == nqxs && pys == nqys) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
}
