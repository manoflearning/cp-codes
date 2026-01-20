#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

optional<string> try_fill(const string &s, char c0, char c1) {
    string ret(sz(s), '.');
    for (int i = 0; i < sz(s); i++) {
        const char c = i & 1 ? c1 : c0;
        if (s[i] != c && s[i] != '?') return nullopt;
        ret[i] = c;
    }
    return ret;
}

optional<string> try_cc(const string &s) { return try_fill(s, 'C', 'C'); }
optional<string> try_ci(const string &s) {
    auto ret = try_fill(s, 'C', 'I');
    return ret ? ret : try_fill(s, 'I', 'C');
}
optional<string> try_cp(const string &s) {
    auto ret = try_fill(s, 'C', 'P');
    return ret ? ret : try_fill(s, 'P', 'C');
}
optional<string> try_ip(const string &s) {
    auto ret = try_fill(s, 'I', 'P');
    return ret ? ret : try_fill(s, 'P', 'I');
}

optional<vector<string>> f(vector<string> a, string op0, string op1) {
    vector<string> ret = a;
    for (int i = 0; i < sz(a); i++) {
        const string op = (i & 1 ? op1 : op0);

        optional<string> res{};
        if (op == "cc") res = try_cc(a[i]);
        if (op == "ci") res = try_ci(a[i]);
        if (op == "cp") res = try_cp(a[i]);
        if (op == "ip") res = try_ip(a[i]);

        if (!res) return nullopt;
        ret[i] = *res;
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<string> a(n);
        for (auto &i : a) cin >> i;

        bool tr = 0;
        vector<string> ans;
        {
            auto res = f(a, "cc", "ip");
            if (res) ans = *res;
            res = f(a, "ip", "cc");
            if (res) ans = *res;
            res = f(a, "ci", "cp");
            if (res) ans = *res;
            res = f(a, "cp", "ci");
            if (res) ans = *res;
        }
        
        vector<string> b(m, string(n, '.'));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) b[j][i] = a[i][j];

        {
            auto res = f(b, "cc", "ip");
            if (res) ans = *res, tr = 1;
            res = f(b, "ip", "cc");
            if (res) ans = *res, tr = 1;
            res = f(b, "ci", "cp");
            if (res) ans = *res, tr = 1;
            res = f(b, "cp", "ci");
            if (res) ans = *res, tr = 1;
        }

        if (!ans.empty()) {
            cout << "yes\n";
            if (tr) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        cout << ans[j][i];
                    }
                    cout << '\n';
                }
            } else {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        cout << ans[i][j];
                    }
                    cout << '\n';
                }
            }
        } else {
            cout << "no\n";
        }
    }
}
