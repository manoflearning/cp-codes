#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const int MAXN = 202020;

int n;
string s;
vector<int> adj[MAXN];

void input() {
    cin >> n >> s;
    s = "*" + s;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int siz[MAXN];
bool used[MAXN];
ll ans = 0;

int get_size(int v, int prv) {
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (!used[i] && i != prv)
            siz[v] += get_size(i, v);
    }
    return siz[v];
}
int get_cent(int v, int prv, int mxsiz) {
    for (auto& i : adj[v]) {
        if (used[i] || i == prv) continue;
        if (siz[i] > mxsiz / 2) return get_cent(i, v, mxsiz);
    }
    return v;
}
void dfs(int v, int prv, int u, int p, int c, map<tuple<int, int>, ll>& mp) {
    u += (s[v] == 'U');
    p += (s[v] == 'P');
    c += (s[v] == 'C');
    mp[{ u - p, u + p - c }]++;
    for (auto& i : adj[v]) {
        if (!used[i] && i != prv)
            dfs(i, v, u, p, c, mp);
    }
}
void cd(int v, int prv) {
    int mxsiz = get_size(v, prv);
    int cent = get_cent(v, prv, mxsiz);

    map<tuple<int, int>, ll> acc;
    acc[{ (s[cent] == 'U') - (s[cent] == 'P'), (s[cent] == 'U') + (s[cent] == 'P') - (s[cent] == 'C') }]++;

    for (auto& i : adj[cent]) {
        if (used[i]) continue;

        map<tuple<int, int>, ll> now;
        dfs(i, cent, 0, 0, 0, now);

        for (auto& it : now) {
            auto [x, y] = it.fr;
            auto w = it.sc;
            if (acc.count({ -x, -y }))
                ans += w * acc[{ -x, -y }];
        }

        for (auto& [key, val] : now) {
            tuple<int, int> nkey = {
                get<0>(key) + (s[cent] == 'U') - (s[cent] == 'P'),
                get<1>(key) + (s[cent] == 'U') + (s[cent] == 'P') - (s[cent] == 'C'),
            };
            acc[nkey] += val;
        }
    }

    used[cent] = 1;
    for (auto& i : adj[cent])
        if (!used[i]) cd(i, v);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cd(1, 0);

    cout << ans;
}
