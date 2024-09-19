#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, -INF);
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return -INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int N;
ll A[505050], B[505050];
ll ans = 0;

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i] >> B[i];
}

void solve() {
    vector<int> ord(1, -1);
    for (int i = 1; i <= N; i++)
        ord.push_back(i);

    sort(ord.begin() + 1, ord.end(), [&](int p1, int p2) {
        return A[p1] < A[p2];
    });

    seg.build(N);

    vector<ll> psum(N + 2);
    for (int i = N; i >= 1; i--) {
        psum[i] = psum[i + 1] + B[ord[i]];
        seg.modify(i, psum[i] + A[ord[i]]);
    }

    for (int i = 1; i <= N; i++) {
        if (i > 0 && A[ord[i - 1]] == A[ord[i]]) continue;

        ll res = 0; // S - A_max + A_min
        res += seg.query(1, i) - psum[i + 1]; // res += S + A_min
        res -= A[ord[i]];

        ans = max(ans, res);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}