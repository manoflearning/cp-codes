#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

namespace linear_sieve {
    vector<int> sp(1010101);
    vector<ll> prime;
    void linear_sieve() {
        for (int i = 2; i < 1010101; i++) {
            if (!sp[i]) {
                prime.push_back(i);
                sp[i] = i;
            }
            for (auto& j : prime) {
                if (i * j >= 1010101) break;
                sp[i * j] = j;
                if (i % j == 0) break;
            }
        }
    }
    map<int, vector<int>> factorization(int x) {
        map<int, vector<int>> ret;
        while (x > 1) {
            int tmp = sp[x];
            if (ret.count(tmp)) ret[tmp][0]++;
            else ret[tmp].resize(1, 1);
            x /= tmp;
        }
        return ret;
    }
};

namespace segment_tree {
    struct Node {
        map<int, vector<int>> mp;
        int len;

        Node operator+(const Node& rhs) const {
            Node ret;
            ret.len = len + rhs.len;

            if (len == 0) return rhs;
            if (rhs.len == 0) return *this;

            vector<int> both, l_only, r_only;
            map<int, vector<int>> mp_l = mp, mp_r = rhs.mp;
            for (auto& i : mp_l) {
                if (!mp_r.count(i.fr)) l_only.push_back(i.fr);
                else both.push_back(i.fr);
            }
            for (auto& i : mp_r) {
                if (!mp_l.count(i.fr)) r_only.push_back(i.fr);
            }

            for (auto& i : both) {
                ret.mp[i].resize(sz(mp_l[i]) + sz(mp_r[i]));
                merge(all(mp_l[i]), all(mp_r[i]), ret.mp[i].begin());
            }
            if (len <= 2) {
                vector<int> tmp(len, 0);
                for (auto& i : r_only) {
                    ret.mp[i].resize(len + sz(mp_r[i]));
                    merge(all(tmp), all(mp_r[i]), ret.mp[i].begin());
                }
            }
            if (rhs.len <= 2) {
                vector<int> tmp(rhs.len, 0);
                for (auto& i : l_only) {
                    ret.mp[i].resize(sz(mp_l[i]) + rhs.len);
                    merge(all(mp_l[i]), all(tmp), ret.mp[i].begin());
                }
            }

            vector<int> lazy_del;
            for (auto& i : ret.mp) {
                if (sz(i.sc) > 3) i.sc.resize(3);
                if (sz(i.sc) == 3 && i.sc[2] == 0) lazy_del.push_back(i.fr);
            }
            for (auto& i : lazy_del) ret.mp.erase(i);

            return ret;
        }
        ll get_value(int k) const {
            ll ret = 1;
            for (auto& i : mp) {
                for (int j = 0; j < i.sc[k]; j++) ret *= i.fr;
            }
            return ret;
        }
    };

    int flag;
    struct Seg {
        vector<Node> t;
        Node e;
        void build(int n, const vector<int>& a) {
            map<int, vector<int>> mp;
            e = { mp, 0 };
            for (flag = 1; flag < n; flag <<= 1);
            t.resize(flag << 1, e);
            for (int i = flag; i < flag + n; i++)
                t[i] = new_node(a[i - flag + 1]);
            for (int i = flag - 1; i >= 1; i--)
                t[i] = t[i << 1] + t[i << 1 | 1];
        }
        void modify(int p, int val) {
            t[p += flag - 1] = new_node(val);
            for (; p > 1; p >>= 1)
                t[p >> 1] = t[p] + t[p ^ 1];
        }
        Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
            if (nr < l || r < nl) return e;
            if (l <= nl && nr <= r) return t[n];
            int mid = (nl + nr) >> 1;
            return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
        }
        Node new_node(int x) {
            map<int, vector<int>> mp = linear_sieve::factorization(x);
            return Node { mp, 1 };
        }
    }seg;
};

int n, m;
vector<int> a;

void input() {
    cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    linear_sieve::linear_sieve();

    input();

    segment_tree::seg.build(n, a);

    while (m--) {
        char op; cin >> op;

        if (op == 'Q') {
            int l, r, k;
            cin >> l >> r >> k;
            cout << segment_tree::seg.query(l, r).get_value(k) << '\n';
        }
        if (op == 'U') {
            int j, x;
            cin >> j >> x;
            segment_tree::seg.modify(j, x);
        }
    }
}