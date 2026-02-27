#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ull = uint64_t;
using pii = pair<int, int>;
using vi = vector<int>;

struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator!=(H o) const { return get() != o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string &str) : ha(sz(str) + 1), pw(ha) {
        pw[0] = 1;
        rep(i, 0, sz(str))
            ha[i + 1] = ha[i] * C + str[i],
            pw[i + 1] = pw[i] * C;
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b - a];
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    
    vector<string> a(n);
    for (auto &i : a) cin >> i;

    string acc{};
    vector<int> cuts(n + 1);

    cuts[0] = 0;
    for (int i = 0; i < n; i++) {
        const string &s = a[i];
        if (sz(s) == 1 && (('a' <= s[0] && s[0] <= 'z') || ('A' <= s[0] && s[0] <= 'Z'))) {
            acc += '*';
        } else {
            acc += s;
        }
        cuts[i + 1] = sz(acc);
    }

    HashInterval ah(acc);

    vector<HashInterval> avh;
    for (int i = 0; i < n; i++) {
        string vars;
        map<char, char> vis; char now = 'a';
        for (int j = i; j < n; j++) {
            const string &s = a[j];
            if (sz(s) == 1 && (('a' <= s[0] && s[0] <= 'z') || ('A' <= s[0] && s[0] <= 'Z'))) {
                if (vis.count(s[0])) vars += vis[s[0]];
                else {
                    vis[s[0]] = ++now;
                    vars += now;
                }
            }
        }
        avh.push_back(HashInterval(vars));
    }
    
    int q; cin >> q;
    while (q--) {
        int m; cin >> m;

        vector<string> b(m);
        for (auto &i : b) cin >> i;

        string bacc, bvars;

        map<char, char> bvis; char now = 'a';
        for (const auto &i : b) {
            if (sz(i) == 1 && (('a' <= i[0] && i[0] <= 'z') || ('A' <= i[0] && i[0] <= 'Z'))) {
                bacc += '*';

                if (bvis.count(i[0])) bvars += bvis[i[0]];
                else {
                    bvis[i[0]] = ++now;
                    bvars += now;
                }
            } else {
                bacc += i;
            }
        }

        HashInterval bh(bacc), bvh(bvars);

        bool yes = 0;
        for (int i = 0; i + m <= n; i++) {
            bool res = 1;
            res &= (bh.hashInterval(0, sz(bacc)) == ah.hashInterval(cuts[i], cuts[i + m]));
            if (res) res &= (bvh.hashInterval(0, sz(bvars)) == avh[i].hashInterval(0, sz(bvars)));
            yes |= res;
        }
        if (yes) cout << "yes\n";
        else cout << "no\n";
    }
}
