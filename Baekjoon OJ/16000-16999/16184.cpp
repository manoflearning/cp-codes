#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

ll n;
vector<pll> arr;
unordered_map<ll, ll> idx;
unordered_map<ll, ll> idx_rev;

void init() {
    arr.clear();
    idx.clear();
    idx_rev.clear();
}

void f(ll x) {
    if (idx.count(x)) return;
    if (x == 1) {
        idx[0] = -1;
        idx_rev[-1] = 0;
        idx[x] = sz(arr);
        idx_rev[sz(arr)] = x;
        arr.push_back({ -1, -1 });
        return;
    }
    
    if (x & 1) {
        f(x / 2);
        f(x / 2 + 1);

        idx[x] = sz(arr);
        idx_rev[sz(arr)] = x;
        arr.push_back({ idx[x / 2 + 1], idx[x / 2] });
    } else {
        f(x / 2);

        idx[x] = sz(arr);
        idx_rev[sz(arr)] = x;
        arr.push_back({ idx[x / 2], idx[x / 2] });
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        cin >> n;

        f(n);

        cout << sz(arr) << '\n';
        for (int i = 0; i < sz(arr); i++) {
            cout << arr[i].fr << ' ' << arr[i].sc << '\n';
        }
        cout << idx[n] << '\n';
    }
}
