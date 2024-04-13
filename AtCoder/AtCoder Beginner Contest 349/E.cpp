// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int a[3][3];
int dp[20000];

const int coy[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };
const int cox[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };
const int p3[] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049 };

vector<vector<int>> checks = {
    { 0, 1, 2 },
    { 3, 4, 5 },
    { 6, 7, 8 },
    { 0, 3, 6 },
    { 1, 4, 7 },
    { 2, 5, 8 },
    { 0, 4, 8 },
    { 2, 4, 6 }
};

int f(int state, int turn) {
    int& ret = dp[state];
    if (ret != -1) return ret;
    
    // finish condition 1
    for (auto& i : checks) {
        bool is_0 = 0, is_1 = 0, is_2 = 0;
        for (auto& j : i) {
            int now = state / p3[j] % 3;
            if (now == 0) is_0 = 1;
            else if (now == 1) is_1 = 1;
            else if (now == 2) is_2 = 1;
        }
        if (!is_0 && is_1 && !is_2) return ret = 1;
        if (!is_0 && !is_1 && is_2) return ret = 2;
    }

    // finish condition 2
    bool no_white = 1;
    ll sc1 = 0, sc2 = 0;
    for (int i = 0; i < 9; i++) {
        int now = state / p3[i] % 3;
        if (now == 0) { no_white = 0; break; }
        else if (now == 1) sc1 += a[coy[i]][cox[i]];
        else if (now == 2) sc2 += a[coy[i]][cox[i]];
    }
    if (no_white) { return ret = (sc1 > sc2 ? 1 : 2); }

    // solve
    ret = 0;

    for (int i = 0; i < 9; i++) {
        int now = state / p3[i] % 3;
        if (now != 0) continue;

        int n_state = state + turn * p3[i];
        int n_turn = (turn == 1 ? 2 : 1);

        int res = f(n_state, n_turn);

        ret = res;
        if (turn == res) break;
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }

    cout << (f(0, 1) == 1 ? "Takahashi" : "Aoki");
}