#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int N, K, L;
string s, t;
set<char> st;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K >> L;
    cin >> s;
    if (L > 0) cin >> t;
    for (auto &i : t) st.insert(i);

    vector<ll> idxs(1, 0);
    for (int i = 1; i <= N; i++) {
        if (st.count(s[i - 1])) idxs.push_back(i);
    }
    idxs.push_back(N + 1);

    ll ans = 0;
    for (int i = 1; i + 1 < sz(idxs); i++) {
        int j = i - K + 1;
        if (j <= 0) continue;
        ans += (idxs[i + 1] - idxs[i]) * (idxs[j] - idxs[j - 1]);
    }

    cout << ans;
}
