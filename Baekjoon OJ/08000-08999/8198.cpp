#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010101;

int n, k;
ll m;
vector<ll> p(MAXN);

void input() {
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) cin >> p[i];
}

inline ll dist(int i, int j) { return abs(p[i] - p[j]); }

vector<int> base(MAXN);
vector<int> dp(MAXN);


bool is_valid(int s, int e, int i) {
    bool cond1 = ((dist(s, i) == dist(e, i) ? (e - s - 1) : (e - s)) <= k);
    bool cond2 = (e - s + 1 > k);
    return cond1 && cond2;
}

void bottomup() {
    // base case
    int s = 1, e = k + 1;
    for (int i = 1; i <= n; i++) {
        while (e < n && dist(s, i) > dist(e + 1, i)) {
            s++, e++;
        }
        assert(is_valid(s, e, i));
        if (dist(s, i) == dist(e, i) || dist(s, i) > dist(e, i)) base[i] = s;
        else base[i] = e;
    }

    iota(dp.begin() + 1, dp.begin() + n + 1, 1);

    // inductive step
    while (m) {
        if (m & 1) {
            for (int i = 1; i <= n; i++) dp[i] = base[dp[i]];
        }
        vector<int> tmp = base;
        for (int i = 1; i <= n; i++) base[i] = tmp[base[i]];
        m >>= 1;
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

    bottomup();

    for (int i = 1; i <= n; i++)
        cout << dp[i] << ' ';
}
