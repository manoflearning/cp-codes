// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        string s;
        cin >> s;

        string ans1, ans2;
        ans1.push_back(s[0]);
        bool isChanged = false;
        for (int i = 1; i < sz(s); i++) {
            if (!isChanged && s[i] == '0') ans1.push_back(s[i]);
            else {
                isChanged = true;
                ans2.push_back(s[i]);
            }
        }

        if (!ans1.empty() && !ans2.empty() && stoll(ans1) < stoll(ans2)) cout << ans1 << ' ' << ans2 << '\n';
        else cout << -1 << '\n';
    }
}