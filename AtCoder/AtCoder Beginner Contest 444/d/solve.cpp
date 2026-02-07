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

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    vector<int> suf(202020);
    for (auto &i : a) suf[i]++;
    for (int i = 202020 - 2; i >= 1; i--) suf[i] += suf[i + 1];

    string ans;
    ll rem = 0;
    for (int i = 1; i < 202020; i++) {
        if (rem == 0 && suf[i] == 0) break;
        ans.push_back('0' + (rem + suf[i]) % 10);
        rem = (rem + suf[i]) / 10;
    }

    reverse(all(ans));

    cout << ans;

    return 0;
}
