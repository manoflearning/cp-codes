#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<ll> a(n), b(n - 1);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;

    sort(all(a));
    sort(all(b));

    int j = n - 2;

    vector<ll> ans;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = n - 1; i >= 0; i--) {
        while (j >= 0 && b[j] >= a[i]) {
            pq.push(b[j]);
            j--;
        }

        if (!pq.empty()) pq.pop();
        else ans.push_back(a[i]);
    }

    if (sz(ans) == 1) cout << ans[0];
    else cout << -1;
}
