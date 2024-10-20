#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int n, m;
vector<ll> a;
map<int, pll> b;
vector<ll> ans;

void input() {
    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;
    for (int i = 0; i < m; i++) {
        cin >> b[i].sc;
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        ll h = a[i];

        auto tmp = b;
        for (auto candy : b) {
            if (h <= candy.sc.fr) break;

            ll add = min(h, candy.sc.sc) - candy.sc.fr;
            h += add;

            if (candy.sc.fr + add == candy.sc.sc) tmp.erase(candy.fr);
            else tmp[candy.fr].fr += add;
        }
        b = tmp;

        ans.push_back(h);
    }
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    for (auto& i : ans)
        cout << i << '\n';
}