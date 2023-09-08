// solution 3: priority queue
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 101010;

int n, m, a[MAXN];
int r, vi[MAXN];
vector<pii> adj[MAXN];
priority_queue<pii, vector<pii>, greater<pii>> pq;

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> r;
    for (int i = 0; i < r; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
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

    for (int i = 1; i <= n; i++) {
        pq.push({ a[i], i });
    }

    int ans = 0, cnt = 0;
    while (cnt < m) {
        pii res = pq.top();
        pq.pop();
        if (vi[res.sc]) continue;
        ans = max(ans, res.fr);
        cnt++;
        vi[res.sc] = 1;
        for (auto& i : adj[res.sc]) {
            if (vi[i.sc]) continue;
            a[i.sc] -= i.fr;
            pq.push({ a[i.sc], i.sc });
        }
    }

    cout << ans;
}

// solution 2: segment tree
/*#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 101010;

int flag;
struct Seg {
    const pii e = { 1e9 + 7, 1e9 + 7 };
    vector<pii> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, e);
    }
    void modify(int p, int val) {
        t[p + flag - 1] = { val, p };
        for (p += flag - 1; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    pii query() { return t[1]; }
}seg;

int n, m, a[MAXN];
int r, vi[MAXN];
vector<pii> adj[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> r;
    for (int i = 0; i < r; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
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

    seg.build(n);
    for (int i = 1; i <= n; i++) {
        seg.modify(i, a[i]);
    }

    int ans = 0;
    while (m--) {
        pii res = seg.query();
        ans = max(ans, res.fr);
        for (auto& i : adj[res.sc]) {
            if (vi[i.sc]) continue;
            a[i.sc] -= i.fr;
            seg.modify(i.sc, a[i.sc]);
        }
        vi[res.sc] = 1;
        seg.modify(res.sc, 1e9 + 7);
    }

    cout << ans;
}*/

// solution 1: parametric search + bfs
/*#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 101010;

int n, m, a[MAXN], r;
vector<pii> adj[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> r;
    for (int i = 0; i < r; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
    }
}

int bfs(int ub) {
    vector<int> vi(MAXN), w(MAXN);

    queue<int> q;
    for (int v = 1; v <= n; v++) {
        w[v] = a[v];
        if (w[v] <= ub) {
            q.push(v);
            vi[v] = 1;
        }
    }

    int ret = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        ret++;

        for (auto& i : adj[v]) {
            if (vi[i.sc]) continue;
            w[i.sc] -= i.fr;
            if (w[i.sc] <= ub) {
                q.push(i.sc);
                vi[i.sc] = 1;
            }
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    int l = 1, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (bfs(mid) >= m) r = mid;
        else l = mid + 1;
    }

    cout << l;
}*/