#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

bool is_valid(const string &s) {
    set<string> st;
    for (int i = 0; i < sz(s); i++) {
        string t;
        for (int j = i; j < sz(s); j++) {
            t.push_back(s[j]);
            st.insert(t);
        }
    }
    return sz(st) % 2 == 0;
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
        string s; cin >> s;

        string ans;
        for (int i = 0; i < sz(s); i++) {
            string t(1, s[i]);
            for (int j = i + 1; j < min(i + 3, sz(s)); j++) {
                t.push_back(s[j]);
                if (is_valid(t)) {
                    ans = t;
                    i = sz(s), j = sz(s);
                    break;
                }
            }
        }

        cout << (ans.empty() ? "-1" : ans) << '\n';
    }
}
