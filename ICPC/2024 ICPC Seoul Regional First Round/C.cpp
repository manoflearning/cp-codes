#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 202020;
// const int D = 26;
// const int MOD1 = 1e9 + 7;
// const int MOD2 = 1e9 + 9;
const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        t.clear();
        lazy.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void add(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, n << 1, nl, mid);
        add(l, r, val, n << 1 | 1, mid + 1, nr);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n) {
        if (!lazy[n]) return;
        if (n < flag) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        t[n] += lazy[n];
        lazy[n] = 0;
    }
} seg;

int m, n;
string T, P;

vector<ll> dp(MAXN, INF);

vector<int> getpi(const string &P) {
    vector<int> pi(sz(P));
    for (int i = 1, j = 0; i < sz(P); i++) {
        while (j > 0 && P[i] != P[j]) j = pi[j - 1];
        if (P[i] == P[j]) pi[i] = ++j;
    }
    return pi;
}
vector<int> kmp(const string &T, const string &P) {
    vector<int> ret(sz(T), -1);
    vector<int> pi = getpi(P);
    for (int i = 0, j = 0; i < sz(T); i++) {
        while (j > 0 && T[i] != P[j]) j = pi[j - 1];
        if (T[i] == P[j]) {
            ret[i] = i - j;
            // ret.push_back(i - j);
            if (j == sz(P) - 1) j = pi[j];
            else ++j;
        }
    }
    return ret;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> m >> n;
    cin >> T >> P;

    auto arr = kmp(P, T);
    // for (auto &i : arr) cout << i << ' ';
    // cout << '\n';
    
    seg.build(n + 1);

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        seg.add(1, i, 1);

        // cout << seg.query(1, 1) << '\n';
        
        if (arr[i - 1] != -1) {
            if (arr[i - 1] == 0) dp[i] = (m - (i - arr[i - 1]));
            else {
                if ((m - (i - arr[i - 1])) == 0) dp[i] = min(dp[i], dp[i - m]);
                else dp[i] = min(dp[i], seg.query(arr[i - 1] + 1, i) + (m - (i - arr[i - 1])));
            }
        }

        dp[i] = min(dp[i], 1 + dp[i - 1]);
        seg.add(i, i, dp[i]);
        // seg.add(i + 1, i + 1, dp[i]);
        
        // cout << i << ' ' << arr[i - 1] << ' ' << (i - arr[i - 1]) << ' ' << dp[i] << '\n';
        // cout << i << ' ' << dp[i] << '\n';
    }
    cout << dp[n];
}
