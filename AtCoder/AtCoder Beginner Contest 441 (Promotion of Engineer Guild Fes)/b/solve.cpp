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

    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    vector<bool> a(26), b(26);
    for (char c : s) a[c - 'a'] = 1;
    for (char c : t) b[c - 'a'] = 1;

    int q; cin >> q;
    while (q--) {
        string x; cin >> x;

        bool b1 = 1, b2 = 1;
        for (char c : x) {
            b1 &= a[c - 'a'];
            b2 &= b[c - 'a'];
        }

        cout << (b1 ^ b2 ? (b1 ? "Takahashi" : "Aoki") : "Unknown") << '\n';
    }
}