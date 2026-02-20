#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int K = 50;

const string L = "left";
const string R = "right";
const string F = "flip";

int cnt_queries{};

bool query(string op) {
    cnt_queries++;

    cout << "? " << op << '\n';
    cout.flush();
    bool ret; cin >> ret;
    return ret;
}

void answer(int n) {
    cout << "! " << n << '\n';
    cout.flush();
}

bool is_match(const vector<bool> &s, const vector<bool> &t, int st_s, int st_t, int l) {
    for (int i = 0; i < l; i++)
        if (s[i + st_s] != t[i + st_t]) return 0;
    return 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    mt19937 mt(time(nullptr));
    uniform_int_distribution<int> rng(0, 1);

    vector<bool> p;
    while (sz(p) < K) p.push_back(rng(mt));

    bool now; cin >> now;
    for (int i = 0; i < K; i++) {
        if (now == p[i]) now = query(R);
        else {
            query(F);
            now = query(R);
        }
    }

    reverse(all(p));

    // case 1: if n < K
    vector<bool> match_all(K, 1), log;
    for (int t = 1; cnt_queries < 500; t++) {
        now = query(L);
        log.push_back(now);

        for (int l = 3; l < K; l++) {
            if (t % l) continue;
            
            if (!is_match(p, log, 0, sz(log) - l, l)) match_all[l] = 0;
        }
    }

    for (int l = 3; l < K; l++) {
        if (match_all[l]) { answer(l); exit(0); }
    }

    // case 2: if K <= n
    assert(is_match(p, log, 0, 0, K));

    for (int i = K; i < sz(log); i++) {
        while (i + K > sz(log)) {
            now = query(L);
            log.push_back(now);
        }

        if (is_match(p, log, 0, i, K)) {
            answer(i);
            exit(0);
        }
    }
}
