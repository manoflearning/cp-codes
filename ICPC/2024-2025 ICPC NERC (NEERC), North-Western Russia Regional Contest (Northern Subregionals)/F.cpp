#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int HS = 7 * 60, HE = 9 * 60;

int n;
vector<ll> a, b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        a.push_back(stoi(s.substr(0, 1)) * 60 + stoi(s.substr(2, 2)));
    }

    int ans = 2;
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && a[i + 1] - a[i] <= 10) ans = min(ans, 1);
        if (i + 2 < n && a[i + 2] - a[i] <= 10) ans = min(ans, 0);
    }

    cout << ans;
}
