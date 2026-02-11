#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // INPUT
    string s; cin >> s;
    const int n = sz(s);

    // BUILD SUFFIX ARRAY
    SuffixArray a{s};
    const auto &sa = a.sa;
    const auto &lcp = a.lcp;

    vector<int> rsa(n + 1);
    for (int i = 0; i <= n; i++) rsa[sa[i]] = i;
    
    vector<vector<int>> dp_lcp(n, vector<int>(n));
    for (int i = 1; i <= n; i++) {
        dp_lcp[sa[i]][sa[i]] = n - sa[i];
        for (int j = i + 1; j <= n; j++) {
            dp_lcp[sa[i]][sa[j]] = min(dp_lcp[sa[i]][sa[j - 1]], lcp[j]);
            dp_lcp[sa[j]][sa[i]] = dp_lcp[sa[i]][sa[j]];
        }
    }

    // DYNAMIC PROGRAMMING
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -INF));
    vector<vector<int>> opt(n + 1, vector<int>(n + 1, -1));

    // base case
    for (int i = 1; i <= n; i++) {
        dp[0][i] = 1;
        opt[0][i] = -1;
    }

    // inductive step
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dp[i][j] < dp[i][j - 1]) {
                dp[i][j] = dp[i][j - 1];
                opt[i][j] = opt[i][j - 1];
            }
        }

        for (int j = i + 1; j < n; j++) {
            if (dp[i][j] == -INF) continue;

            // find minimum k s.t. s[i...j] < s[j...k]
            if (rsa[i] > rsa[j] && dp_lcp[i][j] < j - i) continue;
            const int k = j + min(dp_lcp[i][j], j - i) + 1;
            if (n < k) continue;

            if (dp[j][k] < dp[i][j] + 1) {
                dp[j][k] = dp[i][j] + 1;
                opt[j][k] = i;

                // DEBUG
                // cout << i << ' ' << j << ' ' << k << ' ' << dp[j][k] << '\n';
            }
        }
    }

    // BACKTRACE
    int best_j = 0;
    for (int j = 1; j < n; j++)
        if (dp[best_j][n] < dp[j][n]) best_j = j;
    
    vector<string> ans;
    int j = best_j, k = n;
    while (j >= 0) {
        ans.push_back(s.substr(j, k - j));
        int tmp = j;
        j = opt[j][k], k = tmp;
    }
    assert(sz(ans) == dp[best_j][n]);
    reverse(all(ans));
    
    // OUTPUT
    cout << sz(ans) << '\n';
    for (const auto &i : ans) cout << i << '\n';
}
