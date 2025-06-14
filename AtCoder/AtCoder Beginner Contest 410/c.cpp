#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
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

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    iota(all(a), 1);

    int mov = 0;

    while (q--) {
        int op; cin >> op;

        if (op == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            a[(p + mov) % n] = x;
        } else if (op == 2) {
            int p; cin >> p;
            p--;
            cout << a[(p + mov) % n] << '\n';
        } else if (op == 3) {
            int k; cin >> k;
            mov = (mov + k) % n;
        }
    }
}
