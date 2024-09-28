#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int n;
vector<int> p(MAXN), pmax(MAXN);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> p[i];

        for (int i = 1; i <= n; i++) 
            pmax[i] = max(p[i], pmax[i - 1]);

        vector<int> ans;

        int idx = 1;
        while (idx < n) {
            int val = pmax[idx];
            if (idx == val) {
                swap(p[idx], p[idx + 1]);
                ans.push_back(idx++);
            } else idx = val;
        }

        cout << sz(ans) << '\n';
        for (auto& i : ans) cout << i << ' ';
        cout << '\n';
    }
}
