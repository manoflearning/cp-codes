#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, s;
    cin >> n >> s;
    vector<int> t(n);
    for (auto &i : t) cin >> i;

    bool ans = 1;
    if (t[0] > s) ans = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (t[i + 1] > t[i] + s) ans = 0;
    }

    cout << (ans ? "Yes" : "No");
}
