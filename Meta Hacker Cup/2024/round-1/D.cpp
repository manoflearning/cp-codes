#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXS = 101010;
const int MOD = 998'244'353;

string s;
int k;
ll dp[MAXS];

vector<int> a, optx[MAXS];

void init() {
    memset(dp, -1, sizeof(dp));

    a.clear();
    for (int i = 0; i < MAXS; i++) {
        optx[i].clear();
    }
}

void input() {
    cin >> s >> k;
}

ll f(int idx) {
    ll& ret = dp[idx];
    if (ret != -1) return ret;
    if (idx == sz(s)) return ret = 1;
    if (idx > sz(a)) return ret = 0;
    
    ret = 0;

    vector<int> pos;
    if (s[idx] == '?') {
        pos.resize(9);
        iota(all(pos), 1);
    } else {
        int x = s[idx] - '0';
        pos.push_back(x);
    }

    for (auto& x : pos) {
        ll res = 0;
        if (x == 0) {
            res = 0;
        } else if (x == 1) {
            res = (res + f(idx + 1)) % MOD;
            if (idx + 2 <= sz(s)) {
                res = (res + f(idx + 2)) % MOD;
            }
        } else if (x == 2) {
            res = (res + f(idx + 1)) % MOD;
            if (idx + 2 <= sz(s)) {
                if ('0' <= s[idx + 1] && s[idx + 1] <= '6') {
                    res = (res + f(idx + 2)) % MOD;
                }
                if (s[idx + 1] == '?') {
                    res = (res + f(idx + 2)) % MOD;
                }
            }
        } else if (x >= 3) {
            res = (res + f(idx + 1)) % MOD;
        }

        if (res > ret) {
            ret = res;
            optx[idx].clear();
            optx[idx].push_back(x);
        } else if (res == ret) {
            optx[idx].push_back(x);
        }
    }

    return ret;
}

void get_answer(int idx) {
    if (idx == sz(a)) { k--; return; }
    
    if (a[idx] != -1) { get_answer(idx + 1); return; }
    
    f(idx);

    sort(optx[idx].rbegin(), optx[idx].rend());

    for (auto& i : optx[idx]) {
        get_answer(idx + 1);
        if (k == 0) { a[idx] = i; return; }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        a.resize(sz(s));
        for (int i = 0; i < sz(s); i++) {
            if ('0' <= s[i] && s[i] <= '9')
                a[i] = s[i] - '0';
            else a[i] = -1;
        }

        get_answer(0);

        cout << "Case #" << tt << ": ";
        for (auto& i : a) cout << i;
        cout << ' ';

        cout << f(0) << '\n';
    }
}
