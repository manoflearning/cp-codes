#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int X = 60;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; ll w;
        cin >> n >> w;

        vector<ll> x_to_y[X];
        for (int i = 0; i < n; i++) {
            int x; ll y;
            cin >> x >> y;
            x_to_y[x].push_back(y);
        }

        for (int x = 0; x < X; x++) {
            sort(all(x_to_y[x]));

            
        }
    }
}
