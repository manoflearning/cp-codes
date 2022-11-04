#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int a, b, k, pw[10];
int dp[4040404];
int vi[4040404];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> a >> b >> k;

    for (int i = 0; i < 10; i++) {
        int x = 1;
        for (int j = 0; j < k; j++) x *= i;
        pw[i] = x;
    }

    ll ans = 0;
    for (ll i = a; i <= b; i++) {
        if (dp[i]) {
            ans += dp[i];
            continue;
        }

        vector<int> arr(1, i);
        vi[i] = 1;

        int mn = 1e9;
        while (1) {
            string s = to_string(arr.back());
            
            int res = 0;
            for (auto& c : s) 
                res += pw[c - '0'];
            arr.push_back(res);
            if (vi[res]) break;
            if (dp[res]) { mn = dp[res]; break; }
            vi[res] = 1;
        }

        for (auto& j : arr) vi[j] = 0;
        
        int st = sz(arr);
        for (int i = 0; i < sz(arr); i++) {
            if (arr[i] == arr.back()) {
                st = i; break;
            }
        }
        
        for (int i = st; i < sz(arr); i++) {
            mn = min(mn, arr[i]);
        }

        for (int i = st; i < sz(arr); i++) {
            dp[arr[i]] = mn;
        }
        
        for (int i = st - 1; i >= 0; i--) {
            mn = min(mn, arr[i]);
            dp[arr[i]] = mn;
        }

        ans += mn;
    }

    cout << ans;

	return 0;
}