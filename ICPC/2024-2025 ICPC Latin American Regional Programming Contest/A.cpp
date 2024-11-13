#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string s; cin >> s;

    int ans = sz(s);

    vector<bool> vis(26);
    for (int i = sz(s) - 1; i >= 0; i--) {
        if (vis[s[i] - 'A']) {
            break;
        }

        ans--;
        vis[s[i] - 'A'] = 1;
    }

    cout << ans;
}
