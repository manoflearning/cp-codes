#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;
const int N = 101010;

int flag;
struct Seg {
    vector<int> t;
    void init(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p) {
        for (t[p += flag - 1]++; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n;
vector<pii> a;
ll p2[N], ans = 0;

void init() {
    p2[0] = 1;
    for (int i = 1; i < N; i++)
        p2[i] = 2 * p2[i - 1] % MOD;
}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) 
        cin >> i.fr >> i.sc;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    sort(all(a));

    seg.init(2 * n);

    for (int i = 0; i < n; i++) {
        int lcnt = i, rcnt = n - i - 1;

        ll res = p2[lcnt - seg.query(a[i].fr, 2 * n)] * p2[rcnt];
        ans = (ans + res) % MOD;

        seg.add(a[i].sc);
    }

    cout << ans;
}