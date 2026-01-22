#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

bool yes = 1;
deque<int> ans;

void f(ll n, ll h) {
    ll now = h - 2 * n + 1;
    ans.push_front(2 * n - 1);

    for (ll i = n - 1; i >= 1; i--) {
        if (now <= (i - 1) * (i - 1) && now != (i - 1) * (i - 1) - 2) {
            ans.push_back(2 * i - 1);
        } else {
            now -= 2 * i - 1;
            ans.push_front(2 * i - 1);
        }
    }
}

void solve(ll n, ll h) {
    if (h < 2 * n - 1 || n * n < h) { yes = 0; return; }
    if (h == n * n - 2) { yes = 0; return; }

    if (h - (2 * n - 1) == 2) {
        solve(n - 1, h - 1);
        ans.push_front(2 * n - 1);
    } else { f(n, h); }
}

void fuck(ll n, ll h) {
    yes = 1;
    ans.clear();

    solve(n, h);

    if (yes) {
        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    } else {
        cout << "impossible\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, h;
    cin >> n >> h;
    
    fuck(n, h);

    // DEBUG
    // for (ll n = 1; n <= 20; n++) {
    //     for (ll h = 1; h <= n * n + 5; h++) {
    //         cout << "n = " << n << ", h = " << h << '\n';
    //         fuck(n, h);
    //         cout.flush();
    //     }
    // }
}
