#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        mp[s]++;
    }

    string opt{};
    int opt_cnt{};
    for (auto &[k, v] : mp) {
        if (v > opt_cnt) {
            opt = k, opt_cnt = v;
        }
    }

    cout << opt << '\n';
}