#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int x; cin >> x;

        if (x >= 0) {
            int acc = 0;
            int opt = -1;
            for (int i = 1; ; i++) {
                acc += i;
                if ((x == acc || x + 2 < acc) && (x & 1) == (acc & 1)) { opt = i; break; }
            }

            assert(opt != -1);

            int diff = acc - x;

            assert(!(diff & 1));
            assert(diff == 0 || diff > 2);

            diff /= 2;

            cout << opt << '\n';
            vector<string> ans;
            for (int i = opt; i >= 1; i--) {
                if (i == 1) ans.push_back("1");
                else if (diff == i || diff - i > 1) {
                    diff -= i;
                    ans.push_back(to_string(-i));
                } else {
                    ans.push_back("+" + to_string(i));
                }
            }
            reverse(all(ans));
            for (auto &i : ans) {
                cout << i;
            }
            cout << '\n';

            // for (int i = 1; i <= opt; i++) {
            //     if (i > 1) {
            //         if (i == diff / 2) cout << '-';
            //         else cout << '+';
            //     }
            //     cout << i;
            // }
            // cout << '\n';
        } else {
            int acc = 0;
            int opt = -1;
            for (int i = 1; ; i++) {
                acc += i * (i == 1 ? 1 : -1);
                if ((x == acc || acc < x - 2) && (x % 2) == (acc % 2)) { opt = i; break; }
            }

            assert(opt != -1);

            int diff = x - acc;

            assert(!(diff % 2));
            assert(diff == 0 || diff > 2);

            diff /= 2;

            cout << opt << '\n';
            vector<string> ans;
            for (int i = opt; i >= 1; i--) {
                if (i == 1) ans.push_back("1");
                else if (diff == i || diff - i > 1) {
                    diff -= i;
                    ans.push_back("+" + to_string(i));
                } else {
                    ans.push_back(to_string(-i));
                }
            }
            reverse(all(ans));
            for (auto &i : ans) {
                cout << i;
            }
            cout << '\n';
        }
    }
}