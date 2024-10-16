#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> psum[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;

    for (int i = 0; i <= n; i++) psum[i].resize(k);

    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        for (int j = 0; j < k; j++) {
            psum[i][j] = (x & (1 << j) ? 1 : 0) + psum[i - 1][j];
        }
    }

    int ans = 0;

    map<vector<int>, int> L, R; 
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j < k; j++) 
            psum[i][j] -= psum[i][0];
        psum[i][0] = 0;

        if (L.find(psum[i]) == L.end()) L[psum[i]] = i;
        R[psum[i]] = i;
        ans = max(ans, R[psum[i]] - L[psum[i]]);
    }

    cout << ans;
}