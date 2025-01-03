#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(),(x).end()

int n;
vector<pii> a;
int dp[101010];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) 
        cin >> i.fr >> i.sc;
}

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

void solve() {
    seg.build(505050);

    // base case
    dp[0] = 1; 
    seg.modify(a[0].sc, dp[0]);
    int res = 0;

    // inductive step
    for (int i = 1; i < n; i++) {
        int x = a[i].sc;

        dp[i] = 1 + seg.query(1, x - 1);
        seg.modify(x, dp[i]);

        if (dp[res] < dp[i]) res = i;
    }

    // construct answer
    int ans1 = n - dp[res];

    vector<int> deleted(n, 1);
    while (1) {
        deleted[res] = 0;
        if (dp[res] == 1) break;
        for (int i = res - 1; i >= 0; i--) {
            if (a[i].sc >= a[res].sc) continue;
            if (dp[i] + 1 != dp[res]) continue;
            res = i; break;
        }
    }

    // print answer
    cout << ans1 << '\n';
    for (int i = 0; i < n; i++) {
        if (deleted[i]) cout << a[i].fr << '\n';
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

    sort(all(a));

    solve();
}