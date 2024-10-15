#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

int n;
string s;
ll ans = 0;

namespace CD {
const int MAXN = 202020;

vector<int> adj[MAXN], cdchd[MAXN];
int siz[MAXN], cdpar[MAXN];
bool used[MAXN];

int getSize(int v, int prv) {
  siz[v] = 1;
  for (auto i : adj[v]) {
    if (used[i] || prv == i) continue;
    siz[v] += getSize(i, v);
  }
  return siz[v];
}
int getCent(int v, int prv, int mxsiz) {
  for (auto &i : adj[v]) {
    if (used[i] || i == prv) continue;
    if (siz[i] > mxsiz / 2) return getCent(i, v, mxsiz);
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
  int mxsiz = getSize(v, prv);
  int cent = getCent(v, prv, mxsiz);
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
  for (auto i : adj[cent])
    if (!used[i]) cd(i, cent);
}
}

void input() {
    cin >> n >> s;
    s = "*" + s;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        CD::adj[u].push_back(v);
        CD::adj[v].push_back(u);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    CD::cd(1, 0);

    cout << ans;
}
