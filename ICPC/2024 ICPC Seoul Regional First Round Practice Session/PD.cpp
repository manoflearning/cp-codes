#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int l = 0, r = n - 2;
        while (l < r) {
            int mid = (l + r) >> 1;

            cout << "READ " << mid << endl;
            
            string s; cin >> s;
            if (s == "true") l = mid;
            if (s == "false") r = mid - 1;
        }

        cout << "OUTPUT " << l << endl;
    }
}
