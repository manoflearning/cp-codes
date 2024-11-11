#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010101;

ll s[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int x = 1; x < MAXN; x++) {
        for (int y = 2 * x; y < MAXN; y += x) s[y] += x;
    }
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        if (s[n] == n) cout << "perfect\n";
        else if (s[n] < n) cout << "deficient\n";
        else if (s[n] > n) cout << "abundant\n";
    }
}
