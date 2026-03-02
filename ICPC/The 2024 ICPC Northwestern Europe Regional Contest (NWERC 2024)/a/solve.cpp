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
    cin.ignore();

    map<string, string> mp;
    for (int i = 0; i < n; i++) {
        string v;
        getline(cin, v);
        
        string k;
        bool st = 0;
        for (int j = 0; j < sz(v); j++) {
            if ('A' <= v[j] && v[j] <= 'Z') st = 1;
            if (st) k.push_back(v[j]);
        }
        mp[k] = v;
    }
    for (auto &[_, v] : mp) {
        cout << v << '\n';
    }
}
