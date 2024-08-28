#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()
#define ll long long

int n;
vector<pii> a;

vector<int> xtoy[202020], ytox[202020];

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

    vector<int> c;
    for (auto& i : a) {
        c.push_back(i.fr);
        c.push_back(i.sc);
    }
    sort(all(c));
    c.erase(unique(all(c)), c.end());

    for (auto& i : a) {
        i.fr = lower_bound(all(c), i.fr) - c.begin();
        i.sc = lower_bound(all(c), i.sc) - c.begin();
        xtoy[i.sc].push_back(i.fr);
        ytox[i.fr].push_back(i.sc);
    }

    for (int i = 0; i < 202020; i++) {
        sort(all(xtoy[i]));
        sort(all(ytox[i]));
    }

    ll ans = 0;
    for (auto& [y, x] : a) {
        int lcnt = lower_bound(all(ytox[y]), x) - ytox[y].begin();
        int rcnt = ytox[y].end() - upper_bound(all(ytox[y]), x);

        int dcnt = lower_bound(all(xtoy[x]), y) - xtoy[x].begin();
        int ucnt = xtoy[x].end() - upper_bound(all(xtoy[x]), y);

        if (lcnt <= 0 || rcnt <= 0 || dcnt <= 0 || ucnt <= 0) continue;

        ans += 2ll * dcnt * rcnt * ucnt * lcnt;
    }

    cout << ans;
}
