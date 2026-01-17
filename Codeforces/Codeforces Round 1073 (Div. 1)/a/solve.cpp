#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s;
        cin >> n >> s;

        string t = s;
        sort(all(t));

        if (s == t) {
            cout << "Bob\n";
        } else {
            cout << "Alice\n";

            int z = 0, o = 0;
            for (char c : s) {
                z += c == '0';
                o += c == '1';
            }

            vector<int> ans;
            for (int i = 0; i < z; i++) {
                if (s[i] == '1') ans.push_back(i);
            }
            for (int i = z; i < n; i++) {
                if (s[i] == '0') ans.push_back(i);
            }

            cout << sz(ans) << '\n';
            for (int i : ans) cout << i + 1 << ' ';
            cout << '\n';
        }
    }
}
