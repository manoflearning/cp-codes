#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998'244'353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 202020;

int n, a[MAXN];
int dp[MAXN];
int cnt[MAXN];
// dp[i] = number of possible sets in range [1, i] 
// (including ith square painted as black)

// ans = sum(dp[i])

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
}

unordered_map<int, int> mp[MAXN];
unordered_map<int, int> pdp[MAXN];
unordered_set<int> st;

const int ub = 100;

inline bool isCase1(int idx) {
    return a[idx] / 2 <= cnt[a[idx]];
}

void solve() { // O(N sqrt(N) log (Nsqrt(N)))
    dp[1] = 1;
    if (isCase1(1)) {
        pdp[a[1]][1 % a[1]] = 1;
        st.insert(a[1]);
    }
    else mp[1 + a[1]][a[1]] = 1;

    for (int i = 2; i <= n; i++) {
        for (auto& j : st) {
            dp[i] = (dp[i] + pdp[j][i % j]) % MOD;
        }
        for (auto& j : mp[i]) {
            dp[i] = (dp[i] + j.sc) % MOD;
            if (i + j.fr <= n) {
                auto& it = mp[i + j.fr][j.fr];
                mp[i + j.fr][j.fr] = (mp[i + j.fr][j.fr] + j.sc) % MOD;
            }
        }

        mp[i].clear();

        if (dp[i] && i + a[i] <= n) {
            if (isCase1(i)) {
                pdp[a[i]][i % a[i]] = (pdp[a[i]][i % a[i]] + dp[i]) % MOD;
                st.insert(a[i]);
            }
            else mp[i + a[i]][a[i]] = (mp[i + a[i]][a[i]] + dp[i]) % MOD;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + dp[i]) % MOD;
    cout << ans;
}