#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e17;

int flag;
struct Node {
    ll sum, mx, lmx, rmx;
    Node operator+(const Node& rhs) const {
        Node ret;
        ret.sum = sum + rhs.sum;
        ret.mx = max({ mx, rhs.mx, rmx + rhs.lmx });
        ret.lmx = max(lmx, sum + rhs.lmx);
        ret.rmx = max(rhs.rmx, rmx + rhs.sum);
        return ret;
    }
};
const Node e = { 0, -INF, -INF, -INF };
struct Seg {
    vector<Node> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, { 0, 0, 0, 0 });
    }
    void modify(int p, ll x) {
        t[p += flag - 1].sum += x;
        t[p].mx = t[p].lmx = t[p].rmx = t[p].sum;
        for (; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return e;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int N, M;
struct Operation { int L, R; ll X; };
vector<Operation> op(1);
vector<pair<ll, int>> add[101010];

int Q;
struct Query { int K, S, T, idx; };
vector<Query> qu;
vector<ll> ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> N >> M;
    op.resize(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> op[i].L >> op[i].R >> op[i].X;
        add[op[i].L].push_back({ op[i].X, i });
        add[op[i].R + 1].push_back({ -op[i].X, i });
    }
    cin >> Q;
    qu.resize(Q);
    ans.resize(Q);
    for (int i = 0; i < Q; i++) {
        cin >> qu[i].K >> qu[i].S >> qu[i].T;
        qu[i].idx = i;
    }

    // sorting
    sort(all(qu), [&](const Query& lhs, const Query& rhs) {
        return lhs.K < rhs.K;
    });

    // solve
    seg.build(M);
    int loc = 0;
    for (int i = 1; i <= N; i++) {
        for (auto& j : add[i]) {
            seg.modify(j.second, j.first);
            // cout << i << ' ' << j.second << ' ' << j.first << '\n';
            // cout << seg.query(j.second, j.second).sum << '\n';
        }
        // cout << seg.query(6, 6).sum << '\n';
        while (loc < sz(qu) && qu[loc].K <= i) {
            ans[qu[loc].idx] = seg.query(qu[loc].S, qu[loc].T).mx;
            // cout << qu[loc].idx << ' ' << ans[qu[loc].idx] << '\n';
            loc++;
        }
        // cout << '\n';
    }

    // output
    for (int i = 0; i < Q; i++)
        cout << ans[i] << '\n';
}