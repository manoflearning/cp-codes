#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size() 
#define fr first
#define sc second
#define pii pair<int, int>
#define ll long long

int n;
vector<int> a;

inline ll Hash(int x, int y) {
    return 1000000001ll * x + y;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(all(a));

    int ans = 0;

    //
    int cnt = 0;
    for (int i = 0; i < sz(a); i++) {
        if (i > 0 && a[i] != a[i - 1]) cnt = 0;

        cnt++;
        ans = max(ans, cnt);
    }

    a.erase(unique(all(a)), a.end());

    //
    unordered_map<ll, int> dp;

    for (int j = 0; j < sz(a); j++) {
        for (int i = j - 1; i >= 0; i--) {
            ll now = Hash(j, a[j] - a[i]);
            ll prv = Hash(i, a[j] - a[i]);

            auto it = dp.find(prv);
            auto& it2 = dp[now];
            if (it == dp.end()) it2 = 2;
            else it2 = it->sc + 1;

            ans = max(ans, it2);
        }
    }

    cout << ans;

	return 0;
}