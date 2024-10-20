#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

int n;
vector<pll> a;
map<pll, int> mp;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
        i.fr *= 2, i.sc *= 2;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (auto& i : a) mp[i]++;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pll p;
            p.fr = (a[i].fr + a[j].fr) >> 1;
            p.sc = (a[i].sc + a[j].sc) >> 1;
            mp[p] += 2;
        }
    }

    int ans = 0;
    for (auto& i : mp) {
        ans = max(ans, i.sc);
    }

    cout << ans;
}