#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll K = 1e18;

int flag;    // array size
struct Seg { // 1-indexed
    vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void modify(int p, ll value) { // set value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(K, t[p] + t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) / 2;
        return min(K, query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg[2];


int naive_cal_max_k(int n) {
    int ret = 0;

    vector<int> p(n);
    iota(all(p), 1);
    do {
        bool is_valid = 1;
        for (int i = 0; i + 1 < n; i++) {
            is_valid &= (p[i + 1] >= p[i] - 1);
        }
        ret += is_valid;
    } while (next_permutation(all(p)));

    return ret;
}

bool is_valid(int n, const vector<int> &ans) {
    bool ret = 1;
    ret &= (sz(ans) == n);
    set<int> st;
    for (int i = 0; i + 1 < sz(ans); i++) {
        ret &= (ans[i + 1] >= ans[i] - 1);
        st.insert(ans[i]);
    }
    st.insert(ans.back());
    ret &= (sz(st) == n);
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        ll k;
        cin >> n >> k;

        vector<array<ll, 2>> dp(n + 2);
        vector<array<ll, 2>> sdp(n + 2);

        {
            // base case
            dp[n][0] = 1, dp[n][1] = 0;
            sdp[n][0] = 1, sdp[n][1] = 0;

            // inductive step
            for (int i = n - 1; i >= 1; i--) {
                dp[i][0] = min(K, 1 + sdp[i + 1][1]);
                dp[i][1] = min(K, 1 + sdp[i + 2][0] + sdp[i + 2][1]);
                sdp[i][0] = min(K, dp[i][0] + sdp[i + 1][0]);
                sdp[i][1] = min(K, dp[i][1] + sdp[i + 1][1]);
            }

            seg[0].build(n + 1);
            seg[1].build(n + 1);
            for (int i = 1; i <= n + 1; i++) {
                seg[0].modify(i, dp[i][0]);
                seg[1].modify(i, dp[i][1]);
            }
        }

        if (dp[1][0] + dp[1][1] < k) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> ans;

        ll rem = k;
        int idx = 1;
        bool is_inc = (rem <= dp[1][0]);
        if (!is_inc) rem -= dp[1][0];

        while (idx <= n) {
            int lb = sz(ans) + 1;

            // DEBUG
            // cout << idx << ' ' << is_inc << ' ' << rem << '\n';
            // for (auto &i : ans) cout << i << ' ';
            // cout << "\n\n";

            if (is_inc) {
                if (rem == 1) {
                    for (int x = lb; x <= n; x++) {
                        ans.push_back(x);
                    }
                    rem = 0;
                    idx = n + 1;
                    continue;
                }

                int l = idx + 1, r = n;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (rem <= 1 + sdp[mid][1]) l = mid;
                    else r = mid - 1;
                }

                for (int x = lb; x <= l - 1; x++) {
                    ans.push_back(x);
                }

                rem -= 1 + sdp[l + 1][1];
                idx = l;
                is_inc = 0;
            } else {
                ll acc = 0;

                int l = idx + 2, r = n + 1;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (rem <= seg[0].query(idx + 2, mid) + seg[1].query(idx + 2, mid)) r = mid;
                    else l = mid + 1;
                }
                acc += seg[0].query(idx + 2, l - 1) + seg[1].query(idx + 2, l - 1);
                
                ll ub = lb + (l - idx) - 1;
                for (int x = ub; x >= lb; x--) {
                    ans.push_back(x);
                }

                if (rem <= acc + dp[l][0]) {
                    rem -= acc;
                    idx = l;
                    is_inc = 1;
                } else {
                    rem -= acc + dp[l][0];
                    idx = l;
                    is_inc = 0;
                }
            }
        }

        assert(is_valid(n, ans));

        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}
