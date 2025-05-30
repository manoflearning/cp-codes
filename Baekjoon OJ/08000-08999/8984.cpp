#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

struct Stick {
    int t, d; ll len;
};

struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return v < rhs.v;
    }
};

int n;
ll l;
vector<Stick> stick;
vector<wv> adj[101010][2];
vector<ll> dp[101010][2];

void input() {
    cin >> n >> l;
    stick.resize(n);
    for (auto& i : stick) {
        cin >> i.t >> i.d;
        i.len = abs(i.t - i.d);
    }
}

void cc() {
    vector<ll> ct(1, -INF), cd(1, -INF);
    for (auto& i : stick) {
        ct.push_back(i.t);
        cd.push_back(i.d);
    }

    sort(all(ct));
    sort(all(cd));
    ct.erase(unique(all(ct)), ct.end());
    cd.erase(unique(all(cd)), cd.end());

    for (auto& i : stick) {
        i.t = lower_bound(all(ct), i.t) - ct.begin();
        i.d = lower_bound(all(cd), i.d) - cd.begin();
    }
}

ll f(int idx, int bit, int lb) {
    ll& ret = dp[idx][bit][lb];
    if (lb == sz(adj[idx][bit])) return ret = 0;
    if (ret != -1) return ret;

    ret = 0;

    ret = max(ret, f(idx, bit, lb + 1));

    int v = adj[idx][bit][lb].v;
    ll w = adj[idx][bit][lb].w;

    wv du = { 0, idx };
    int nlb = upper_bound(all(adj[v][!bit]), du) - adj[v][!bit].begin();
    ret = max(ret, f(v, !bit, nlb) + w);

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    cc();

    for (auto& i : stick) {
        adj[i.t][0].push_back({ i.len + l, i.d });
        adj[i.d][1].push_back({ i.len + l, i.t });
    }

    for (int i = 0; i < 101010; i++) {
        sort(all(adj[i][0]));
        sort(all(adj[i][1]));
        dp[i][0].resize(sz(adj[i][0]) + 1, -1);
        dp[i][1].resize(sz(adj[i][1]) + 1, -1);
    }

    ll ans = 0;
    for (int i = 1; i < 101010; i++) {
        for (int j = 0; j < sz(adj[i][0]); j++) {
            ans = max(ans, f(i, 0, j));
        }
        for (int j = 0; j < sz(adj[i][1]); j++) {
            ans = max(ans, f(i, 1, j));
        }
    }

    cout << ans;

	return 0;
}