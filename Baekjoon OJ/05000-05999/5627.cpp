#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
const int MAX = 2500 * 4 + 1;

int N, M, K;
int eny, enx;
pair<pii, int> bac[5];
vector<vector<int>> a[5];

void input() {
    cin >> N >> M >> K;
    cin >> eny >> enx;
    for (int i = 0; i < K; i++) {
        auto& it = bac[i];
        char c;
        cin >> it.fr.fr >> it.fr.sc >> c;
        if (c == 'U') it.sc = 0;
        if (c == 'R') it.sc = 1;
        if (c == 'D') it.sc = 2;
        if (c == 'L') it.sc = 3;

        a[i].resize(N + 2, vector<int>(M + 2));
        for (int y = 1; y <= N; y++) {
            string s; cin >> s;
            for (int x = 1; x <= M; x++) {
                a[i][y][x] = s[x - 1] - '0';
            }
        }
    }
}

vector<pair<pii, int>> path[5];

void getOnePath(pair<pii, int> now, vector<vector<int>>& dir, vector<pair<pii, int>>& res) {
    res.push_back({ { -1, -1 }, -1 });
    res.push_back(now);
    while (sz(res) < 2 * MAX + 1) {
        now.sc = (now.sc + dir[now.fr.fr][now.fr.sc]) % 4;
        if (now.sc == 0) { if (now.fr.fr == 1) now.sc = 2; }
        else if (now.sc == 1) { if (now.fr.sc == M) now.sc = 3; }
        else if (now.sc == 2) { if (now.fr.fr == N) now.sc = 0; }
        else if (now.sc == 3) { if (now.fr.sc == 1) now.sc = 1; }

        now.fr.fr += dy[now.sc];
        now.fr.sc += dx[now.sc];

        res.push_back(now);
    }
}

void getAllPath() {
    for (int i = 0; i < K; i++) {
        getOnePath(bac[i], a[i], path[i]);
    }
}

void extremeCase() {
    for (int t = 1; t <= MAX; t++) {
        int isDone = 1;
        for (int i = 0; i < K; i++) {
            if (path[i][t].fr.fr != eny) isDone = 0;
            if (path[i][t].fr.sc != enx) isDone = 0;
        }
        if (isDone) { cout << t; exit(0); }
    }
}

vector<pll> cg[5];

void getCongruence() {
    for (int i = 0; i < K; i++) {
        set<pair<pii, int>> vi;
        int mod = 0;
        vector<int> ent;
        for (int t = MAX + 1; t <= 2 * MAX; t++) {
            if (vi.count(path[i][t])) {
                mod = t - (MAX + 1);
                break;
            }
            if (path[i][t].fr.fr == eny && path[i][t].fr.sc == enx) {
                ent.push_back(t - (MAX + 1));
            }
            vi.insert(path[i][t]);
        }

        for (auto& j : ent) {
            cg[i].push_back({ j, mod });
        }
    }
}

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll minv(ll x, ll y) {
    if (x == 0 && y == 1) return 0;
    if (x == 1) return 1;
    return y - minv(y % x, x) * y / x;
}
pll crt(pll U, pll V) {
    if (U.sc == -1 || V.sc == -1) return { -1, -1 };
    if (U.sc == 1) return V;
    if (V.sc == 1) return U;
    ll g = gcd(U.sc, V.sc), l = U.sc * V.sc / g;
    if ((V.fr - U.fr) % g) return { -1, -1 };

    ll u = U.sc / g, v = V.sc / g;
    ll mul = (V.fr - U.fr) / g;
    mul = mul * minv(u % v, v) % v;

    pll ret = { mul * U.sc + U.fr, l };
    ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
    return ret;
}

ll ans = -1;

void bt(int v, pll res) {
    if (res.fr == -1) return;
    if (v == K) {
        if (ans == -1 || res.fr < ans) ans = res.fr;
        return;
    }

    for (auto& i : cg[v])
        bt(v + 1, crt(res, i));
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getAllPath();

    extremeCase();

    getCongruence();

    for (auto& i : cg[0]) bt(1, i);
    cout << (ans == -1 ? ans : ans + MAX + 1);
}