#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int MAXN = 40404;
const ll INF = 1e18;

int n;
ll sx, sy[MAXN], ey[MAXN], ex[MAXN];
int slope[4 * MAXN];
ll mny = INF, mxy = -INF;

void init() {
    mny = INF, mxy = -INF;
}

void input() {
    cin >> n >> sx;
    for (int i = 0; i < n; i++) {
        cin >> sy[i] >> ey[i] >> ex[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> slope[4 * i] >> slope[4 * i + 1] >> slope[4 * i + 2] >> slope[4 * i + 3];
    }
}

bool is_impossible() {
    int pos_cnt = 0, neg_cnt = 0;
    for (int i = 0; i < 4 * n; i++) {
        if (slope[i] > 0) pos_cnt++;
        else neg_cnt++;
    }
    return pos_cnt < n || neg_cnt < n;
}

void cal_cow_y(ll sl, ll x, ll y) {
    ll res_y = y - sl * x;
    mny = min(mny, res_y);
    mxy = max(mxy, res_y);
}

void solve() {
    vector<pii> only_pos, only_neg;
    vector<int> both;
    for (int i = 0; i < n; i++) {
        only_pos.push_back({ ex[i], sy[i] });
        only_neg.push_back({ ex[i], ey[i] });
        both.push_back(sy[i]);
        both.push_back(ey[i]);
    }

    vector<int> pos, neg;
    for (int i = 0; i < 4 * n; i++) {
        if (slope[i] > 0) pos.push_back(slope[i]);
        else neg.push_back(slope[i]);
    }

    sort(all(pos));
    sort(rall(neg));

    // both
    vector<int> cow_for_both;
    for (int i = n; i < sz(neg); i++) {
        cow_for_both.push_back(neg[i]);
    }
    neg.resize(n);
    for (int i = n; i < sz(pos); i++) {
        cow_for_both.push_back(pos[i]);
    }
    pos.resize(n);
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (is_impossible()) {
            cout << -1 << '\n';
            continue;
        }

        solve();

        cout << mxy - mny << '\n';
    }
}
