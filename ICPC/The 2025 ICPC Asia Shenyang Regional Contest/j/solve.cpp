#pragma GCC optimize ("Ofast, unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;
constexpr int BLK = 454;
constexpr ll N = 202020;

struct Query {
    int l, r, v;
    bool operator<(const Query &rhs) const {
        return pii{l / BLK, r ^ (l / BLK & 1)} < pii{rhs.l / BLK, rhs.r ^ (rhs.l / BLK & 1)};
    }
};

inline ll _hash(int dist, int b, int e) {
    return dist * N * N + b * N + e;
}

void add(const int x, map<int, int> &mp, set<ll> &st, const int mod) {
    auto &now = mp[x];
    now++;
    if (now >= 2) return;

    auto itr = mp.upper_bound(x);
    if (itr == mp.end()) itr = mp.begin();

    auto itl = itr;
    if (itl == mp.begin()) itl = mp.end(), itl--;
    else itl--;
    if (itl == mp.begin()) itl = mp.end(), itl--;
    else itl--;

    if (sz(mp) >= 2) {
        const int b = x;
        const int e = itr->first;
        const int dist = (b - e + mod) % mod;
        st.insert(_hash(dist, b, e));
    }
    if (sz(mp) >= 2) {
        const int b = itl->first;
        const int e = x;
        const int dist = (b - e + mod) % mod;
        st.insert(_hash(dist, b, e));
    }
    if (sz(mp) >= 3) {
        const int b = itl->first;
        const int e = itr->first;
        const int dist = (b - e + mod) % mod;
        st.erase(_hash(dist, b, e));
    }
}
void del(const int x, map<int, int> &mp, set<ll> &st, const int mod) {
    auto &now = mp[x];
    now--;
    if (now >= 1) return;

    auto itr = mp.upper_bound(x);
    if (itr == mp.end()) itr = mp.begin();

    auto itl = itr;
    if (itl == mp.begin()) itl = mp.end(), itl--;
    else itl--;
    if (itl == mp.begin()) itl = mp.end(), itl--;
    else itl--;

    if (sz(mp) >= 2) {
        const int b = x;
        const int e = itr->first;
        const int dist = (b - e + mod) % mod;
        st.erase(_hash(dist, b, e));
    }
    if (sz(mp) >= 2) {
        const int b = itl->first;
        const int e = x;
        const int dist = (b - e + mod) % mod;
        st.erase(_hash(dist, b, e));
    }
    if (sz(mp) >= 3) {
        const int b = itl->first;
        const int e = itr->first;
        const int dist = (b - e + mod) % mod;
        st.insert(_hash(dist, b, e));
    }

    mp.erase(x);
}
int calc(const int v, const map<int, int> &mp, const set<ll> &st, const int mod) {
    int ret = INF;
    auto it = st.begin();
    while (it != st.end()) {
        const int e = *it % N;
        int b = *it / N % N;
        b += (b < e) * mod;

        bool res = 0;
        res |= (e <= v && v <= b);
        res |= (e <= v + mod && v + mod <= b);
        if (res) {
            ret = min<int>(ret, *it / (N * N));
            break;
        }

        it++;
    }

    auto itr = mp.upper_bound(v);
    if (itr == mp.end()) itr = mp.begin();

    auto itl = itr;
    if (itl == mp.begin()) itl = mp.end(), itl--;
    else itl--;
    if (itl->first == v) {
        if (itl == mp.begin()) itl = mp.end(), itl--;
        else itl--;
    }

    int dist1 = v - itr->first;
    if (dist1 < 0) dist1 += mod;
    int dist2 = itl->first - v;
    if (dist2 < 0) dist2 += mod;
    ret = min({ret, dist1, dist2});

    return ret;
}

vi mo(const vector<int> &a, const int mod, const vector<Query> &qu) {
    vi s(sz(qu)), res = s;
    iota(all(s), 0);
    sort(all(s), [&](int i, int j) {
        return qu[i] < qu[j];
    });

    map<int, int> mp;
    set<ll> st;

    int L = qu[s[0]].l, R = qu[s[0]].r;
    for (int i = L; i < R; i++) add(a[i], mp, st, mod);

    for (int qi : s) {
        Query q = qu[qi];
        while (L > q.l) add(a[--L], mp, st, mod);
        while (R < q.r) add(a[R++], mp, st, mod);
        while (L < q.l) del(a[L++], mp, st, mod);
        while (R > q.r) del(a[--R], mp, st, mod);
        res[qi] = calc(q.v, mp, st, mod);
    }

    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q, m;
    cin >> n >> q >> m;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    vector<Query> qu(q);
    for (auto &i : qu) {
        cin >> i.l >> i.r >> i.v;
        i.l--;
    }

    auto ans = mo(a, m, qu);
    for (auto &i : ans) cout << i << '\n';
}

