#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int Q = 202020;

int q, w;
int l[Q], r[Q];
set<int> sl, sr;

void input() {
    cin >> q >> w;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;

        l[i] = max(x - y, 0);
        r[i] = min(x + y, w);
    }
}

int leftmost(int i) {
    auto it = sr.lower_bound(l[i]);
    return *it;
}
int rightmost(int i) {
    auto it = sl.upper_bound(r[i]);
    if (it == sl.begin()) return r[i];
    it--;
    
}

void solve() {
    for (int i = q; i <= q; i++) {
        auto it = 
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

    cout << fixed;
    cout.precision(8);

    solve();
}