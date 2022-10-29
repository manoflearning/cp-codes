#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll s, k;
        cin >> s >> k;

        if (k & 1) {
            if (s & 1) cout << 1 << '\n';
            else cout << 0 << '\n';
        }
        else {
            
        }
    }

    return 0;
}