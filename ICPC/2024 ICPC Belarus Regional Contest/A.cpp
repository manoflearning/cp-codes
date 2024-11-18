#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 202020;

int n, k;
int a[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> ans(n);

    for (int i = 1; i <= k + 1; i++) {
        for (int j = i + 1; j <= k + 2; j++) {
            vector<int> res;
            for (int p = 1; p <= j; p++) {
                if (p != i && p != j) res.push_back(p);
            }

            int prv = j;
            for (int p = j + 1; p <= n; p++) {
                if (a[j] - a[i] == a[p] - a[prv]) {
                    prv = p;
                } else res.push_back(p);

                if (sz(res) > k) break;
            }

            if (sz(res) <= k && sz(res) < sz(ans)) ans = res;
        }
    }

    if (sz(ans) == n) {
        cout << -1;
        exit(0);
    }

    cout << sz(ans) << '\n';
    for (auto &i : ans) cout << i << ' ';
}
