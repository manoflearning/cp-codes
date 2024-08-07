#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

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
    ll g = gcd(U.sc, V.sc);
    ll l = U.sc * V.sc / g;
    if ((V.fr - U.fr) % g) return { -1, -1 };

    ll u = U.sc / g, v = V.sc / g;
    ll mul = (V.fr - U.fr) / g;
    mul = mul * minv(u % v, v) % v;

    pll ret = { mul * U.sc + U.fr, l };
    ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
    return ret;
}

const int MAXN = 131313;

ll N, M, L;
ll H[MAXN], W[MAXN];
ll ans[MAXN];

void input() {
    cin >> N >> M >> L;
    for (int i = 0; i < N; i++) cin >> H[i];
    for (int i = 0; i < M; i++) cin >> W[i];
}

vector<ll> chain;

void part1() {
    vector<ll> sumH;
    for (int co = 0; co < L; co++) { // O(N + L)
        pll res = crt({ 0, M }, { co, L });
        if (res.fr != -1) {
            ll sum = 0;
            while (res.fr < N * M) {
                sum += H[res.fr / M];
                res.fr += res.sc;
            }
            sumH.push_back(sum);            
        }
        else sumH.push_back(0);
    }

    vector<ll> ord;
    vector<int> idx(L, -1);
    for (int r = 0; r < N; r++) { // O(N)
        int co = (M * r + 1) % L;
        if (!ord.empty() && ord[0] == sumH[co]) break;
        idx[co] = sz(ord);
        ord.push_back(sumH[co]);
    }

    int po = 0;
    while (sz(ord) < M + L) 
        ord.push_back(ord[po++]);

    for (int co = 0; co < L; co++) {
        if (idx[co] == -1) chain.push_back(0);
        else chain.push_back(ord[idx[co]]);
    }
}

const int MAXD = 18;

vector<pll> base;
ll dp[MAXD + 1];

void part2() {
    // first column
    map<ll, ll> mp;
    for (int c = 0; c < M; c++) {
        ans[0] += chain[(M * L - c) % L] * W[c];
        mp[chain[(M * L - c) % L]] += W[c];
    }

    for (auto& i : mp) {
        base.push_back({ i.fr, i.sc });
    }

    // sparse table
    dp[0] = 0;
    

    // naive
    // for (int c = 0; c < M; c++) {
    //     for (int co = 0; co < L; co++) {
    //         ans[co] += chain[(co - c + M * L) % L] * W[c];
    //         cout << chain[(co - c + M * L) % L] << ' ';
    //     }
    //     cout << '\n';
    // }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    part1();
    part2();

    for (int co = 0; co < L; co++)
        cout << ans[co] << '\n';
}