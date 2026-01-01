#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;
    
    map<pair<string, set<char>>, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        string s, t;
        cin >> s >> t;

        set<char> st;
        for (auto &c : t) st.insert(c);

        while (!s.empty()) {
            if (st.count(s.back())) {
                s.pop_back();
            } else {
                break;
            }
        }

        mp[{s, st}].push_back(i + 1);
    }

    cout << sz(mp) << '\n';
    for (auto &[_, v] : mp) {
        cout << sz(v) << ' ';
        for (auto &i : v) cout << i << ' ';
        cout << '\n';
    }
}