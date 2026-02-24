#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Node {
    array<Node *, 26> chd{};
    array<int, 26> comp{};
    ll cnt_all, cnt_leaf;

    ~Node() {
        for (int i = 0; i < 26; i++)
            if (chd[i]) delete chd[i];
    }
    void insert(int i, int used, const vector<int> &s, const vector<int> &w) {
        cnt_all++;
        if (i == sz(s)) { cnt_leaf++; return; }

        const int now = s[i], rem = w[i] - used;
        assert(rem > 0);

        if (chd[now] && comp[now] != rem) {
            if (comp[now] < rem) {
                chd[now]->insert(i, used + comp[now], s, w);
            } else {
                Node * tmp_chd = chd[now];
                int tmp_comp = comp[now];

                chd[now] = new Node{};
                comp[now] = rem;
                chd[now]->insert(i + 1, 0, s, w);

                assert(chd[now]->chd[now] == nullptr);

                chd[now]->chd[now] = tmp_chd;
                chd[now]->comp[now] = tmp_comp - rem;

                chd[now]->cnt_all += tmp_chd->cnt_all;
            }
        } else {
            if (chd[now] == nullptr) {
                chd[now] = new Node{};
                comp[now] = rem;
            }
            chd[now]->insert(i + 1, 0, s, w);
        }
    }
    void count(int i, int used, const vector<int> &s, const vector<int> &w, vector<tuple<Node *, int>> &log) {
        if (i == sz(s)) return;

        if (used == w[i]) {
            this->count(i + 1, 0, s, w, log);
            return;
        }

        if (!used) log.push_back({this, 0});

        const int now = s[i], rem = w[i] - used;
        assert(rem > 0);

        get<1>(log.back()) += cnt_leaf;
        for (int j = 0; j < now; j++) {
            if (chd[j]) get<1>(log.back()) += chd[j]->cnt_all;
        }

        // DEBUG
        // cout << i << ' ' << (char)(s[i] + 'a') << ' ' << rem << ' ' << get<1>(log.back()) << '\n';
        // for (int j = 0; j < 26; j++) {
        //     if (chd[j]) cout << (char)(j + 'a') << ' ' << chd[j]->cnt_all << '\n';
        // }

        if (chd[now]) {
            const int both = min(comp[now], rem);
            if (comp[now] == both) chd[now]->count(i, used + both, s, w, log);
            else {
                if (i + 1 < sz(s) && now < s[i + 1]) {
                    get<1>(log.back()) += chd[now]->cnt_all;
                }
                while (sz(log) < sz(s)) log.push_back({nullptr, 0});
            }
        } else {
            while (sz(log) < sz(s)) log.push_back({nullptr, 0});
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    string tgt;
    cin >> tgt;

    const int m = sz(tgt);

    vector<string> d(n);
    for (auto &i : d) cin >> i;
    
    Node *root = new Node{};

    for (const string &str : d) {
        vector<int> s, w;
        for (int i = 0; i < sz(str); i++) {
            if (s.empty() || s.back() != str[i] - 'a') {
                s.push_back(str[i] - 'a');
                w.push_back(1);
            } else {
                w.back()++;
            }
        }
        root->insert(0, 0, s, w);
    }

    vector<int> s, w;
    vector<tuple<Node *, int>> log;
    for (int i = 0; i < m; i++) {
        if (s.empty() || s.back() != tgt[i] - 'a') {
            s.push_back(tgt[i] - 'a');
            w.push_back(1);
        } else {
            w.back()++;
        }
    }

    root->count(0, 0, s, w, log);

    int ans = 0;
    for (auto &[_, i] : log) ans += i;
    cout << ans << '\n';

    while (q--) {
        int k; char c;
        cin >> k >> c;
        k--;

        const int now = c - 'a';

        int len = m;
        while (len > k) {
            assert(!s.empty());

            const int both = min(len - k, w.back());
            const int tmp_s = s.back(), tmp_w = w.back();

            len -= both;
            ans -= get<1>(log.back());

            s.pop_back();
            w.pop_back();
            log.pop_back();

            if (both < tmp_w) {
                s.push_back(tmp_s);
                w.push_back(tmp_w - both);
                break;
            }
        }
        
        assert(len == k);

        if (s.empty() || s.back() != now) {
            s.push_back(now);
            w.push_back(m - k);
        } else {
            w.back() += m - k;
            if (sz(s) == sz(log)) {
                ans -= get<1>(log.back());
                log.pop_back();
            }
        }

        int t = sz(log);
        
        // DEBUG
        // cout << t << ' ' << (char)(s[t] + 'a') << ' ' << w[t] << ' ' << sz(s) << '\n';
        
        if (log.empty()) root->count(t, 0, s, w, log);
        else {
            Node *st = get<0>(log.back());
            ans -= get<1>(log.back());
            log.pop_back();

            t = sz(log);

            if (st) {
                st->count(t, 0, s, w, log);
            } else {
                while (sz(log) < sz(s)) log.push_back({nullptr, 0});
            }
        }

        // DEBUG
        // for (int i = 0; i < sz(s); i++)
        //     cout << string(w[i], s[i] + 'a');
        // cout << '\n';

        for (int i = t; i < sz(log); i++) ans += get<1>(log[i]);
        cout << ans << '\n';

        assert(sz(s) == sz(w));
        assert(sz(s) == sz(log));
    }

    delete root;
}