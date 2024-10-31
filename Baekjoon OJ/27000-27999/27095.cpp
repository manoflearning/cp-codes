#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int dy[] = {1, 0, -1, 0};
const int dx[] = {0, 1, 0, -1};

struct UF {
    vector<int> par, siz;
    void build(int n) {
        par.resize(n + 1, -1);
        siz.resize(n + 1, 0);
    }
    int find(int x) {
        if (par[x] < 0) return x;
        return par[x] = find(par[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        par[U] = V;
        siz[V] += siz[U];
    }
    void add_size(int p) { siz[find(p)]++; }
} uf;

inline int Hash(int y, int x) { return y * 202 + x; }

int rgn[202][202];
vector<pair<tuple<__int128_t, __int128_t, __int128_t, __int128_t>, int>> mp; 

void dfs(__int128_t sy, __int128_t ey, __int128_t sx, __int128_t ex) {
    assert(sy <= ey);
    assert(sx <= ex);
    string s; cin >> s;
    if (s == "vsplit" || s == "hsplit" || s == "-1" || s == "-2") {
        if (s == "vsplit" || s == "-1") {
            __int128_t mid = (sx + ex) / 2;
            dfs(sy, ey, sx, mid);
            dfs(sy, ey, mid + 1, ex);
        }
        if (s == "hsplit" || s == "-2") {
            __int128_t mid = (sy + ey) / 2;
            dfs(sy, mid, sx, ex);
            dfs(mid + 1, ey, sx, ex);
        }
    } else mp.push_back({{sy, ey, sx, ex}, stoi(s)});
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dfs(-1e36, 1e36, -1e36, 1e36);

    // coordinate compression
    vector<__int128_t> yy(1, -4e36), xx(1, -4e36);
    for (auto &[key, val] : mp) {
        yy.push_back(get<0>(key));
        yy.push_back(get<1>(key));
        xx.push_back(get<2>(key));
        xx.push_back(get<3>(key));
    }
    sort(all(yy)); sort(all(xx));
    yy.erase(unique(all(yy)), yy.end());
    xx.erase(unique(all(xx)), xx.end());

    for (auto &[key, val] : mp) {
        tuple<__int128_t, __int128_t, __int128_t, __int128_t> nkey = {
            lower_bound(all(yy), get<0>(key)) - yy.begin(),
            lower_bound(all(yy), get<1>(key)) - yy.begin(),
            lower_bound(all(xx), get<2>(key)) - xx.begin(),
            lower_bound(all(xx), get<3>(key)) - xx.begin(),
        };
        key = nkey;
    }

    // union find
    uf.build(Hash(sz(yy), sz(xx)));
    for (auto &[key, val] : mp) {
        uf.add_size(Hash(get<0>(key), get<2>(key)));
        for (int y = get<0>(key); y <= get<1>(key); y++)
            for (int x = get<2>(key); x <= get<3>(key); x++) rgn[y][x] = val;
    }

    for (int y = 1; y < sz(yy); y++) {
        for (int x = 1; x < sz(xx); x++) {
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 1 || sz(yy) <= ny || nx < 1 || sz(xx) <= nx) continue;
                if (rgn[y][x] == rgn[ny][nx])
                    uf.merge(Hash(y, x), Hash(ny, nx));
            }
        }
    }

    int ans = 0;
    for (int y = 1; y < sz(yy); y++) {
        for (int x = 1; x < sz(xx); x++) {
            ans = max(ans, uf.siz[uf.find(Hash(y, x))]);
        }
    }

    cout << ans;
}
