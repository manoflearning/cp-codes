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

        vector<int> vis(n + 1), ans;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            int j = i;
            do {
                vis[j] = 1;
                ans.push_back(j);
                j = a[j];
            } while (j != i);
        }

        for (auto& i : ans)
            cout << i << ' ';
        cout << '\n';
    }
}