#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int n;
vector<pll> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
    }

    map<pll, int> mp;
    for (int i = 0; i < n; i++) {
        mp[{a[i].fr + a[i].fr, a[i].sc + a[i].sc}]++;
        for (int j = i + 1; j < n; j++) {
            pll res = {(a[i].fr + a[j].fr), (a[i].sc + a[j].sc)};
            mp[res] += 2;
        }
    }

    int ans = 0;
    for (auto& [_, res] : mp)
        ans = max(ans, res);
    
    cout << ans;
}
