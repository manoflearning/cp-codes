#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    vector<int> vis(6);
    for (int i = 0; i < 4; i++) {
        int x; cin >> x;
        vis[x] = 1;
    }

    for (int i = 1; i <= 5; i++)
        if (!vis[i]) cout << i;
}
