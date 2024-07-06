#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<pii> p(n);
        int idx = 1;
        for (auto& i : p) {
            i.fr = idx++;
            cin >> i.sc;
        }

        sort(all(p), [&](const pii& p1, const pii& p2) {
            return max(p1.fr, p1.sc) < max(p2.fr, p2.sc);
        });

        for (auto& i : p) {
            cout << i.fr << ' ';
        }
        cout << '\n';
    }
}