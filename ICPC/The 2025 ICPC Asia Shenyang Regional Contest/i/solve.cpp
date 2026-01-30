#pragma GCC optimize ("O3")
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
    
    set<pair<int, int>> st;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        if (c < 240) {
            if (!st.count({a, b})) {
                cout << b << '\n';
                st.insert({a, b});
                mp[a]++;
            } else cout << 0 << '\n';
        } else {
            if (!st.count({a, b}) && mp[a] < 3) {
                cout << b << '\n';
                st.insert({a, b});
                mp[a]++;
            } else cout << 0 << '\n';
        }
    }
}
