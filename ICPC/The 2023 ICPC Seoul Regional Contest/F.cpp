#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 10101;
const int INF = 1e9 + 7;

int n, K;
vector<pii> a;

void input() {
    cin >> n >> K;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;
}

vector<int> cc;
void coor_comp() {
    cc.push_back(-INF);
    for (auto& i : a) {
        cc.push_back(i.fr);
        cc.push_back(i.sc);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (auto& i : a) {
        i.fr = lower_bound(all(cc), i.fr) - cc.begin();
        i.sc = lower_bound(all(cc), i.sc) - cc.begin();
    }
}

int psum[MAXN << 1][MAXN << 1];

vector<vector<int>> dp;
void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    int& res = dp[gr][mid];
    res = -INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        int val = dp[gr - 1][i] + psum[mid][mid] - psum[i][mid];
        if (res < val) {
            res = val, idx = i;
        }
    }
    if (l < r) {
        f(gr, l, mid, nl, idx);
        f(gr, mid + 1, r, idx, nr);
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

    coor_comp();

    for (auto& i : a) {
        psum[i.fr][i.fr]++;
        psum[i.fr][i.sc + 1]--;
    }
    for (int i = 1; i < sz(cc); i++) {
        for (int j = 1; j < sz(cc); j++) {
            psum[i][j] += psum[i - 1][j];
            psum[i][j] += psum[i][j - 1];
            psum[i][j] -= psum[i - 1][j - 1];
        }
    }

    dp.resize(K + 1, vector<int>(sz(cc)));
    for (int i = 1; i < sz(cc); i++) {
        dp[1][i] = psum[i][i];
    }
    for (int i = 2; i <= K; i++) {
        f(i, 0, sz(cc) - 1, 0, sz(cc) - 1);
    }

    int ans = 0;
    for (auto& i : dp)
        for (auto& j : i) ans = max(ans, j);
    cout << ans;
}
