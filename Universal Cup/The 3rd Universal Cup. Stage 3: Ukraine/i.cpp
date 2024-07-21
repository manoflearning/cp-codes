#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> p(n + 1);
        for (int i = 1; i <= n; i++) cin >> p[i];

        vector<pii> pairs;
        for (int i = 1; i <= n; i++) {
            pairs.push_back({ i, p[i] });
        }

        vector<bool> vis(n + 1);
        for (int cnt = 0; cnt < n; cnt++) {
            int opt = -1;
            for (int i = 1; i <= n; i++) {
                if (vis[i]) continue;
                if (opt == -1) opt = i;
                else if (pairs[i].fr < pairs[opt].fr && pairs[i].sc < pairs[opt].sc) opt = i;
                else if ()
            }

            vis[opt] = 1;
            cout << opt << ' ';
        }
        cout << '\n';
    }
}

// n <= ans <= 2n

// if p1.fr < p2.fr and p1.sc < p2.sc
// => p1 < p2
// otherwise
// => 