#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        bool yes = 0;

        unordered_set<string> st2, st3;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;

            if (s[0] == s[sz(s) - 1]) yes = 1;

            if (sz(s) == 1) continue;

            string t = s;
            swap(t[0], t[sz(t) - 1]);
            if (sz(t) == 2) {
                yes |= st2.count(t);

                st2.insert(s);
                st3.insert(s + "*");
            }
            if (sz(t) == 3) {
                yes |= st3.count(t);
                yes |= st3.count(t.substr(0, 2) + "*");

                st2.insert(s.substr(0, 2));
                st3.insert(s);
            }
        }

        cout << (yes ? "YES" : "NO") << '\n';
    }
}
