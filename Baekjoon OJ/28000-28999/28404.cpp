#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;
const int LMT = 86;

ll fi[505];
set<ll> fist;
map<ll, ll> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    fi[1] = 1, fi[2] = 2;
    fist.insert(1);
    fist.insert(2);
    for (int i = 3; fi[i - 2] + fi[i - 1] <= INF; i++) {
        fi[i] = fi[i - 2] + fi[i - 1];
        fist.insert(fi[i]);
    }

    a[1] = 1, a[2] = 2, a[3] = 3;
    a[4] = 6;

    ll j = 4;
    while (1) {
        if (j > LMT) break;
        assert(a.count(j));
        assert(!a.count(a[j]));
        a[a[j]] = fi[j];
        j = a[j];
    }
    for (int i = 7; i <= LMT; i++) {
        if (a.count(i) || fist.count(i)) continue;

        a[i] = (fist.count(i + 1) ? i + 2 : i + 1);
        a[a[i]] = fi[i];

        ll j = a[i];
        while (1) {
            if (j > LMT) break;
            assert(a.count(j));
            assert(!a.count(a[j]));
            a[a[j]] = fi[j];
            j = a[j];
        }
    }

    // for (auto& [k, v] : a) {
    //     cout << k << ' ' << v << '\n';
    // }

    int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;

        if (a.count(n)) {
            cout << a[n] << '\n';
        }
        else {
            ll res = n;
            for (auto i : fist) {
                if (i >= n) break;
                res--;
            }

            if (res & 1) {
                ll ans = (a.count(n + 1) ? n + 2 : n + 1);
                
                cout << (ans <= INF ? ans : -1) << '\n';
            } else cout << -1 << '\n';
        }
    }
}
