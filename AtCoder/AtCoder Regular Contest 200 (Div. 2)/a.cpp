#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

bool is_valid(int n, const vector<ll> &a, const vector<ll> &b, const vector<ll> &x) {
    ll suma = 0, sumb = 0;
    for (int i = 0; i < n; i++) {
        suma += a[i] * x[i];
        sumb += b[i] * x[i];
    }
    assert(suma + sumb == 0);
    return suma > 0 && sumb < 0;
}

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

        vector<ll> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int p1, int p2) {
            return a[p1] * b[p2] < a[p2] * b[p1];
        });

        if (a[ord[0]] * b[ord[n - 1]] == a[ord[n - 1]] * b[ord[0]]) {
            cout << "No\n";
        } else {
            cout << "Yes\n";

            vector<ll> x(n);
            x[ord[0]] = -(a[ord[n - 1]] + b[ord[n - 1]]);
            x[ord[n - 1]] = (a[ord[0]] + b[ord[0]]);
            for (auto &i : x) cout << i << ' ';
            cout << '\n';

            assert(is_valid(n, a, b, x));
        }
    }
}
