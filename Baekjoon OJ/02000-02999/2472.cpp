#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pll pair<ll, ll>
#define fr first
#define sc second

const ll INF = 1e18;
const int MAX = 101010;

struct wv {
	ll w; int v;
	bool operator<(const wv& rhs) const {
		return w > rhs.w;
	}
};

int n, m, A, B, C;
vector<wv> adj[MAX];
vector<ll> dista(MAX, INF), distb(MAX, INF), distc(MAX, INF);

void input() {
    cin >> n;
    cin >> A >> B >> C;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dijkstra(int st, vector<ll>& dist) {
	priority_queue<wv> pq;

	pq.push({ 0, st });
	dist[st] = 0;

	while (!pq.empty()) {
		int v = pq.top().v;
		ll w = pq.top().w;
		pq.pop();

		if (w > dist[v]) continue;

		for (auto& i : adj[v]) {
			if (dist[i.v] > w + i.w) {
				dist[i.v] = w + i.w;
				pq.push({ w + i.w, i.v });
			}
		}
	}
}

struct Point {
    ll x, y, z;
    int idx;
};

int isAns[MAX];
vector<Point> a;
vector<ll> xx, yy, zz;

void cc() {
    xx.push_back(-INF);
    yy.push_back(-INF);
    zz.push_back(-INF);
    for (auto& i : a) {
        xx.push_back(i.x);
        yy.push_back(i.y);
        zz.push_back(i.z);
    }

    sort(all(xx));
    sort(all(yy));
    sort(all(zz));
    xx.erase(unique(all(xx)), xx.end());
    yy.erase(unique(all(yy)), yy.end());
    zz.erase(unique(all(zz)), zz.end());

    for (auto& i : a) {
        i.x = lower_bound(all(xx), i.x) - xx.begin();
        i.y = lower_bound(all(yy), i.y) - yy.begin();
        i.z = lower_bound(all(zz), i.z) - zz.begin();
    }
}

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
        p += flag - 1;
        t[p] = min(t[p], value);
		for (; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    //
    input();

    dijkstra(A, dista);
    dijkstra(B, distb);
    dijkstra(C, distc);

    //
    for (int v = 1; v <= n; v++) {
        a.push_back({ dista[v], distb[v], distc[v], v });
    }

    cc();

    sort(all(a), [&](const Point& u, const Point& v) {
        if (u.x ^ v.x) return u.x < v.x;
        else if (u.y ^ v.y) return u.y < v.y;
        else return u.z < v.z;
    });

    seg.build(MAX);
    vector<pll> arr;
    for (int i = 0; i < sz(a); i++) {
        if (i > 0 && a[i].x > a[i - 1].x) {
            for (auto& j : arr) {
                seg.modify(j.fr, j.sc);
            }
            arr.clear();
        }

        isAns[a[i].idx] = 1;

        ll res = seg.query(1, a[i].y - 1);
        if (res < a[i].z) isAns[a[i].idx] = 0;

        arr.push_back({ a[i].y, a[i].z });
    }

    //
    int q; cin >> q;
    while (q--) {
        int v; cin >> v;
        cout << (isAns[v] ? "YES" : "NO") << '\n';
    }

    return 0;
}