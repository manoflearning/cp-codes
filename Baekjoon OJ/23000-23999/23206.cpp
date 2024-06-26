#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXX = 90 * 10'000 * 2, MAXY = 180 * 10'000 * 2;

int n;
vector<int> a[MAXX + 100], b[MAXX + 100];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        double xx, yy;
        cin >> xx >> yy;
        int x = (xx + 90) * 10'000 - 0.5;
        int y = (yy + 180) * 10'000 - 0.5;
        x = (x + MAXX) % MAXX;
        y = (y + MAXY) % MAXY;
        a[x].push_back(y);
    }
    for (int i = 0; i < n; i++) {
        double xx, yy;
        cin >> xx >> yy;
        int x = (xx + 90) * 10'000 - 0.5;
        int y = (yy + 180) * 10'000 - 0.5;
        x = (x + MAXX) % MAXX;
        y = (y + MAXY) % MAXY;
        b[x].push_back(y);
    }
}

const int MOD1 = 1e9 + 7, MOD2 = 999'999'107;
const ll d = MAXY + 1;
ll dexp1[404040], dexp2[404040];

void init() {
    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i < 404040; i++) {
        dexp1[i] = d * dexp1[i - 1] % MOD1;
        dexp2[i] = d * dexp2[i - 1] % MOD2;
    }
}

vector<int> rabinKarp(vector<int>& aa, vector<int>& bb) {
    vector<int> ret;

    ll a1 = 0, a2 = 0, b1 = 0, b2 = 0;
    for (int i = 0; i < sz(aa); i++) {
        a1 = (d * a1 + aa[i]) % MOD1;
        a2 = (d * a2 + aa[i]) % MOD2;
        b1 = (d * b1 + bb[i]) % MOD1;
        b2 = (d * b2 + bb[i]) % MOD2;
    }
    if (a1 == b1 && a2 == b2) ret.push_back(0);

    for (int i = 1; i < sz(bb); i++) {
        b1 = (d * (b1 - dexp1[sz(bb) - 1] * bb[i - 1] % MOD1) + bb[i - 1]) % MOD1;
        b1 = (b1 + MOD1) % MOD1;
        b2 = (d * (b2 - dexp2[sz(bb) - 1] * bb[i - 1] % MOD2) + bb[i - 1]) % MOD2;
        b2 = (b2 + MOD2) % MOD2;
        if (a1 == b1 && a2 == b2) ret.push_back(i);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    int isStart = 1;
    set<int> s;

    for (int i = 0; i <= MAXX; i++) {
        if (sz(a[i]) != sz(b[i])) {
            cout << "Different";
            return 0;
        }
        if (a[i].empty()) continue;

        sort(a[i].begin(), a[i].end());
        sort(b[i].begin(), b[i].end());

        vector<int> aa, bb;
        for (int j = 0; j < sz(a[i]); j++) {
            aa.push_back(a[i][(j + 1) % sz(a[i])] - a[i][j]);
            if (aa.back() < 0) aa.back() += MAXY;
            bb.push_back(b[i][(j + 1) % sz(b[i])] - b[i][j]);
            if (bb.back() < 0) bb.back() += MAXY;
        }

        vector<int> res = rabinKarp(aa, bb);
        vector<int> diff;
        for (auto& j : res) 
            diff.push_back((b[i][j] - a[i][0] + MAXY) % MAXY);

        if (isStart) {
            for (auto& j : diff) s.insert(j);
            isStart = 0;
        }
        else {
            set<int> ns;
            for (auto& j : diff)
                if (s.count(j)) ns.insert(j);
            s = ns;
        }
    }

    cout << (sz(s) ? "Same" : "Different");
}