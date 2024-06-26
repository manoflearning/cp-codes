#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int B, Z;
vector<int> P[12];
vector<int> loc[12];
int cycleSt[12], cycleEn[12]; // [cycleSt[i], cycleEn[i])
int cycleLen[12];
vector<int> cycle[12];
int fromZooToTime[12][121];

void input() {
    cin >> B >> Z;
    for (int i = 1; i <= B; i++) {
        for (int j = 0; j <= Z; j++) {
            int x; cin >> x;
            P[i].push_back(x);
        }
    }
}

void sendMeLocation() {
    for (int be = 1; be <= B; be++) {
        vector<int> initTime(121, -1);
        loc[be].push_back(P[be][0]);

        while (sz(loc[be]) <= 3 * Z) {
            int now = loc[be].back(), nxt = P[be][now];
            if (initTime[now] == - 1)
                initTime[now] = sz(loc[be]) - 1;

            if (cycleEn[be] == 0 && initTime[nxt] != -1) {
                cycleSt[be] = initTime[nxt];
                cycleEn[be] = sz(loc[be]);
            }

            loc[be].push_back(nxt);
        }
    }
}

void extremeCase() {
    if (B == 1) {
        cout << loc[1][0] << ' ' << 0;
        exit(0);
    }

    for (int ti = 0; ti <= Z; ti++) {
        int isAns = 1;
        for (int be = 1; be + 1 <= B; be++) {
            if (loc[be][ti] != loc[be + 1][ti]) {
                isAns = 0;
                break;
            }
        }
        if (isAns) {
            cout << loc[1][ti] << ' ' << ti;
            exit(0);
        }
    }
}

void buildCycle() {
    for (int be = 1; be <= B; be++) {
        cycleLen[be] = cycleEn[be] - cycleSt[be];
        memset(fromZooToTime[be], -1, sizeof(fromZooToTime[be]));
        for (int i = 0; i < cycleLen[be]; i++) {
            cycle[be].push_back(loc[be][i + Z + 1]);
            fromZooToTime[be][loc[be][i + Z + 1]] = i;
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

pll solve() {
    pll ret = { -1, -1 };
    for (int zoo = 1; zoo <= Z; zoo++) {
        int isVisited = 1;
        for (int be = 1; be <= B; be++) {
            if (fromZooToTime[be][zoo] == -1) {
                isVisited = 0; break;
            }
        }

        if (!isVisited) continue;

        pll res = crt({ fromZooToTime[1][zoo], cycleLen[1] }, { fromZooToTime[2][zoo], cycleLen[2] });
        for (int be = 3; be <= B; be++) {
            res = crt(res, { fromZooToTime[be][zoo], cycleLen[be] });
        }

        if (res.fr != -1 && (ret.fr == -1 || res.fr < ret.fr)) {
            ret.fr = res.fr, ret.sc = zoo;
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

    sendMeLocation();

    extremeCase();

    buildCycle();

    pll ans = solve();

    if (ans.sc == -1) cout << "*";
    else cout << ans.sc << ' ' << ans.fr + Z + 1;
}