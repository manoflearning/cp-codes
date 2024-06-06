#include <bits/stdc++.h>
using namespace std;

int n, m;
int pr[101010], pc[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n + m; i++) {
        int x, y;
        cin >> x >> y;
        pr[x] ^= 1, pc[y] ^= 1;
    }

    for (int i = 0; i < 101010; i++) {
        if (pr[i] || pc[i]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}