#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<int> vis(n + 1);
        vector<vector<int>> ptt;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            int j = i;
            vector<int> tmp;
            do {
                vis[j] = 1;
                tmp.push_back(j);
                j = a[j];
            } while(j != i);

            ptt.push_back(tmp);
        }

        if (sz(ptt) == 1) {
            cout << n - 2 << '\n';
            
            vector<int> ra(n + 1);
            for (int i = 1; i <= n; i++) ra[a[i]] = i;

            int p1 = -1, p2 = -1;
            for (int i = 0; i < sz(ptt[0]); i++) {
                if (a[ptt[0][i]] == 1 || a[ptt[0][i]] == 2) {
                    if (p1 == -1) p1 = i;
                    else p2 = i;
                }
            }

            cout << (p2 - p1) << '\n';
            for (int i = p1 + 1; i <= p2; i++)
                cout << ptt[0][i] << ' ';
            cout << '\n';
        }
        else {
            cout << n << '\n';
            cout << sz(ptt[0]) << '\n';
            for (auto& i : ptt[0]) cout << i << ' ';
            cout << '\n';
        }
    }
}