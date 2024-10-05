#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n;
vector<pll> a;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

void init() {
}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
        ll g = gcd(abs(i.fr), abs(i.sc));
        i.fr /= g, i.sc /= g;
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

        input();

        sort(all(a));
        a.erase(unique(all(a)), a.end());

        if (sz(a) == 1) {
            cout << sz(a) << '\n';
            for (auto& i : a)
                cout << i.fr << ' ' << i.sc << '\n';
        } else if (sz(a) == 2) {
            cout << sz(a) << '\n';
            cout << a[0].fr << ' ' << a[0].sc << '\n';
            cout << a[1].fr - a[0].fr << ' ' << a[1].sc - a[0].sc << '\n';
        } else {
            
        }
    }
}
