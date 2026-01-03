#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    set<int> vis;
    while (!vis.count(n)) {
        vis.insert(n);
        string s = to_string(n);

        int res = 0;
        for (auto &c : s) res += (c - '0') * (c - '0');

        n = res;
    }

    cout << (n == 1 ? "Yes" : "No");
}
