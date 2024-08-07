#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXT = 500001;
const int MAXL = 500001;
const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, -INF);
    }
    void modify(int p, ll val) {
        if (t[p + flag - 1] >= val) return;
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return -INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}segR, segL;

struct Market { int p; ll w; };

int N, S;
ll lw, rw;
vector<Market> a[505050];

void input() {
    cin >> N >> lw >> rw >> S;
    a[0].push_back({ S, 0 });
    for (int i = 0; i < N; i++) {
        int T, p, w;
        cin >> T >> p >> w;
        a[T].push_back({ p, w });
    }
    a[MAXT].push_back({ S, 0 });
}

void sorting() {
    for (int T = 0; T <= MAXT; T++) {
        sort(all(a[T]), [&](const Market& p1, const Market& p2) {
            return p1.p < p2.p;
        });
    }
}

void modifyL(int p, ll val) { segL.modify(p, val - lw * (p - 1)); }
void modifyR(int p, ll val) { segR.modify(p, val - rw * (MAXL - p)); }
ll queryL(int p) { return segL.query(p + 1, MAXL) + lw * (p - 1); }
ll queryR(int p) { return segR.query(1, p - 1) + rw * (MAXL - p); }

ll dp[505050];

void solve() {
    segL.build(MAXL);
    segR.build(MAXL);
    for (int i = 1; i <= MAXL; i++) dp[i] = -INF;
    
    // base case
    dp[S] = 0;
    modifyL(S, dp[S]);
    modifyR(S, dp[S]);

    // inductive step
    for (int T = 1; T <= MAXT; T++) {
        const auto& arr = a[T];
        if (arr.empty()) continue;

        vector<ll> LR(sz(arr)), RL(sz(arr));
        // LR[i]는 i에서 시작해서 왼쪽으로 이동했다가, 다시 오른쪽으로 이동하여 i에 도착했을 때 얻을 수 있는 최댓값
        // RL[i]는 i에서 시작해서 오른쪽으로 이동했다가, 다시 왼쪽으로 이동하여 i에 도착했을 때 얻을 수 있는 최댓값

        vector<pll> lazyModifyR, lazyModifyL;
        for (int i = 0; i < sz(arr); i++) {
            const auto& it = arr[i];
            LR[i] = it.w;
            if (i == 0) continue;
            LR[i] += max(0ll, LR[i - 1] - (lw + rw) * (it.p - arr[i - 1].p));

            ll res = it.w;
            res += LR[i - 1];
            res += queryL(arr[i - 1].p);
            res -= rw * (it.p - arr[i - 1].p);
            dp[it.p] = max(dp[it.p], res);
            lazyModifyR.push_back({ it.p, res });
        }

        for (int i = sz(arr) - 1; i >= 0; i--) {
            const auto& it = arr[i];
            RL[i] = arr[i].w;
            if (i == sz(arr) - 1) continue;
            RL[i] += max(0ll, RL[i + 1] - (lw + rw) * (arr[i + 1].p - arr[i].p));

            ll res = it.w;
            res += RL[i + 1];
            res += queryR(arr[i + 1].p);
            res -= lw * (arr[i + 1].p - it.p);
            dp[it.p] = max(dp[it.p], res);
            lazyModifyL.push_back({ it.p, res });
        }

        for (auto& i : lazyModifyR) modifyR(i.fr, i.sc);
        for (auto& i : lazyModifyL) modifyL(i.fr, i.sc);

        for (int i = 0; i < sz(arr); i++) {
            const auto& it = arr[i];
            ll res = it.w + queryR(it.p);
            dp[it.p] = max(dp[it.p], res);
            modifyR(it.p, res);
        }
        for (int i = sz(arr) - 1; i >= 0; i--) {
            const auto& it = arr[i];
            ll res = it.w + queryL(it.p);
            dp[it.p] = max(dp[it.p], res);
            modifyL(it.p, res);
        }

        for (auto& i : arr) {
            modifyL(i.p, dp[i.p]);
            modifyR(i.p, dp[i.p]);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sorting();

    solve();

    cout << dp[S];
}