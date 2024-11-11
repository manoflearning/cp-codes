#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    
    tuple<int, int, int> opt = {-1, -1, -1};
    string ans;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        string s;
        cin >> x >> y >> z;
        getline(cin, s);
        if (opt < tuple<int, int, int>(x, y, z)) {
            opt = {x, y, z};
            ans = s;
        }
    }

    for (int i = 1; i < ans.size(); i++) cout << ans[i];
}
