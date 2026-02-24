#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ull = unsigned long long;
using u128 = __uint128_t;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr u128 MOD = ((u128)1 << 64) - 1;

vector<u128> pow26;

int l, n;
vector<string> s;

vector<vector<u128>> val26;

bool f(const vector<int> &&st, int used) {
    if (sz(st) == 1) return true;

    for (int now = 0; now < 26; now++) {
        if (used & (1 << now)) continue;

        bool valid = 1;
        for (const int i : st) {    
            if (!val26[i][now]) { valid = 0; break; }
        }

        if (!valid) continue;

        unordered_map<ull, vector<int>> mp;
        for (const int i : st) {
            mp[val26[i][now]].push_back(i);
        }

        bool ret = true;
        for (auto &[_, v] : mp) {
            ret &= f(std::move(v), used | (1 << now));
        }
        return ret;
    }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cin >> l >> n;
    s.assign(n, string());
    for (auto &i : s) cin >> i;

    pow26.assign(l, 0);
    pow26[0] = 1;
    for (int i = 1; i < l; i++) {
        pow26[i] = (26ull * pow26[i - 1]) % MOD;
    }

    val26.assign(n, vector<u128>(26));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            val26[i][s[i][j] - 'a'] = (val26[i][s[i][j] - 'a'] + pow26[j]) % MOD;
        }
    }

    vector<int> st;
    for (int i = 0; i < n; i++) st.push_back(i);

    const bool ans = f(std::move(st), 0);
    cout << (ans ? "YES" : "NO") << '\n';
}