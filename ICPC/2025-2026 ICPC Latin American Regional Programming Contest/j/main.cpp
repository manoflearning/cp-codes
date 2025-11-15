#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const string a = "ha";
const string b = "boooo";
const string c = "bravo";

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    string s; cin >> s;

    int ans = 0;
    for (int i = 0; i < sz(s); i++) {
        if (i + sz(a) - 1 < sz(s) && s.substr(i, sz(a)) == a) ans += 1;
        if (i + sz(b) - 1 < sz(s) && s.substr(i, sz(b)) == b) ans -= 1;
        if (i + sz(c) - 1 < sz(s) && s.substr(i, sz(c)) == c) ans += 3;
    }

    cout << ans;
}