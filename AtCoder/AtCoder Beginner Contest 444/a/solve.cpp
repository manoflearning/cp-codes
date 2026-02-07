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

    string s; cin >> s;

    bool yes = 1;
    for (int i = 0; i + 1 < sz(s); i++) {
        yes &= s[i] == s[i + 1];
    }

    cout << (yes ? "Yes" : "No");

    return 0;
}
