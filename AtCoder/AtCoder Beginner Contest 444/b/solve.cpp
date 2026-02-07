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

    int n, k;
    cin >> n >> k;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        string s = to_string(i);
        int sum = 0;
        for (char c : s) sum += c - '0';
        if (sum == k) ans++;
    }

    cout << ans << '\n';

    return 0;
}
