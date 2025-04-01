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

    vector<ll> a(n);
    ll sum = 0;
    for (auto& i : a) {
        cin >> i;
        sum += i;
    }

    sort(all(a));

    sum -= a.back();
    if (a.back() <= 2 * sum) cout << (sum + a.back()) / 3;
    else cout << sum;
}
