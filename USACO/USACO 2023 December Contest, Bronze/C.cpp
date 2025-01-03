#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
vector<ll> h, a;
vector<int> t;

void init() {
    h.clear();
    a.clear();
    t.clear();
}

void input() {
    cin >> n;
    h.resize(n);
    a.resize(n);
    t.resize(n);
    for (auto& i : h) cin >> i;
    for (auto& i : a) cin >> i;
    for (auto& i : t) cin >> i;
}

ll solve() {
    vector<int> sorted;
    for (int i = 0; i < n; i++) sorted.push_back(i);

    sort(all(sorted), [&](int i, int j) {
        return t[i] > t[j];
    });

    ll ansl = 0, ansr = LLONG_MAX;
    for (int i = 0; i + 1 < n; i++) {
        int u = sorted[i], v = sorted[i + 1];

        ll curl = -1, curr = -1;

        if (h[u] < h[v] && a[u] <= a[v]) curl = 0, curr = LLONG_MAX;
        if (h[u] < h[v] && a[u] > a[v]) curl = 0, curr = (h[v] - h[u] - 1) / (a[u] - a[v]);
        if (h[u] >= h[v] && a[u] < a[v]) curl = (h[u] - h[v]) / (a[v] - a[u]) + 1, curr = LLONG_MAX;
        if (h[u] >= h[v] && a[u] >= a[v]) curl = -1, curr = -1;

        ansl = max(ansl, curl);
        ansr = min(ansr, curr);
    }
    
    return (ansl <= ansr ? ansl : -1);
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        cout << solve() << '\n';
    }
}