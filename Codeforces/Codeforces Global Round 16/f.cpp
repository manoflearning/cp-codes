#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, m;
vector<ll> a;
vector<pll> b;

void init() {}

void input() {
    cin >> n >> m;
    a.resize(n);
    for (auto &i : a) cin >> i;
    b.resize(m);
    for (auto &[l, r] : b) cin >> l >> r;
}

void remove_b() {
    vector<pll> tmp;
    for (auto &[l, r] : b) {
        int idx = lower_bound(all(a), l) - a.begin();
        if (idx < sz(a) && a[idx] <= r) {
            continue;
        } else {
            tmp.push_back({l, r});
        }
    }
    b = tmp;
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
        sort(all(b));

        remove_b();
    }
}
