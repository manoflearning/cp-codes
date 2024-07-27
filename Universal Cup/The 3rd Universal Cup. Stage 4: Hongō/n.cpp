#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    string s;
    cin >> n >> s;

    vector<ll> cnt(26);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    ll ans = (ll)n * (n - 1) / 2 + n;
    for (int i = 0; i < 26; i++) {
        ans -= cnt[i] * (cnt[i] - 1) / 2;
    }

    cout << ans;
}