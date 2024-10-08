#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXGN = 66;

int f(ll n, ll m, ll k) {
    vector<int> mex(MAXGN);

    if (n > m) swap(n, m); // wlog

    if (n <= k && m <= k) mex[0] = 1;
    else if (n <= k && k < m && m <= 2 * k - 1) {
        mex[0] = 1;
        if ((n * (m - k)) & 1) mex[1] = 1;
    }
    else if (n <= k && 2 * k - 1 < m) {

    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t; cin >> t;

    int ans = 0;
    for (int i = 0; i < t; i++) {
        ll n, m, k;
        cin >> n >> m >> k;

        if (k == 1) {
            ans ^= ((n * m) & 1 ? 1 : 0);
        }
        else ans ^= f(n, m, k);
    }

    cout << (ans ? "Yuto" : "Platina");
}
