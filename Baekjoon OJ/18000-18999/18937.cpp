#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n, dp[101010];
// dp[i] = 1(win), 0(lose).
vector<int> a;

int f(int v) {
    int& ret = dp[v];
    if (ret != -1) return ret;
    if (v == n) return ret = 1;

    if (f(v + 1)) {
        if (a[v] == 3) return ret = 0;
        else return ret = 1;
    }
    else return ret = 1;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

    cin >> n;
    a.push_back(INF);

    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        if (x != 2) a.push_back(x);
    }

    n = sz(a) - 1;
    string s; cin >> s;

    if (n == 0) {
        if (s == "Whiteking") cout << "Blackking";
        else cout << "Whiteking";
        return 0;
    }

    sort(a.rbegin(), a.rend());

    int ans = f(1);
    if (ans) cout << s;
    else {
        if (s == "Whiteking") cout << "Blackking";
        else cout << "Whiteking";
    }

    return 0;
}