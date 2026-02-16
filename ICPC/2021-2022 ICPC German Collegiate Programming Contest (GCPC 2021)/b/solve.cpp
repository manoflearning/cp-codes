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
    
    int idx = -1;
    for (int i = 0; i < sz(s); i++) {
        bool yes = 0;
        yes |= s[i] == 'a';
        yes |= s[i] == 'e';
        yes |= s[i] == 'i';
        yes |= s[i] == 'o';
        yes |= s[i] == 'u';
        if (yes) idx = i;
    }

    assert(idx >= 0);

    s = s.substr(0, idx + 1) + "ntry";
    cout << s << '\n';
}