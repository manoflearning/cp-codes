#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

bool is_expression(const string &s) {
    if (s.empty()) return false;
    
    string acc;
    for (int i = 0; i < sz(s); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            acc += s[i];
        } else {
            if (acc.empty()) return false;
            if (sz(acc) > 10) return false;
            if (sz(acc) > 1 && acc[0] == '0') return false;

            if (s[i] != '+' && s[i] != '-') return false;
            acc.clear();
        }
    }

    if (acc.empty()) return false;
    if (sz(acc) > 10) return false;
    if (sz(acc) > 1 && acc[0] == '0') return false;

    return true;
}

bool is_equality(const string &s) {
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '=') {
            const bool lhs = is_expression(s.substr(0, i));
            const bool rhs = is_expression(s.substr(i + 1, sz(s) - i - 1));
            return lhs && rhs;
        }
    }
    return false;
}

ll get_eval(const string &s) {
    ll ret = 0;

    ll sign{+1};
    string acc{};
    for (const char c : s) {
        if ('0' <= c && c <= '9') {
            acc += c;
        } else {
            ret += stoll(acc) * sign;
            acc.clear();

            assert(c == '+' || c == '-');

            if (c == '+') sign = +1;
            else sign = -1;
        }
    }
    ret += stoll(acc) * sign;
    acc.clear();

    return ret;
}

bool is_correct(const string &s) {
    if (!is_equality(s)) return false;

    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '=') {
            const ll lhs = get_eval(s.substr(0, i));
            const ll rhs = get_eval(s.substr(i + 1, sz(s) - i - 1));
            return lhs == rhs;
        }
    }

    assert(0);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    string s; cin >> s;

    if (is_correct(s)) {
        cout << "Correct\n";
        exit(0);
    }

    for (int i = 0; i < sz(s); i++) {
        if (s[i] < '0' || '9' < s[i]) continue;

        string sp;
        if (i > 0) sp += s.substr(0, i);
        if (i + 1 < sz(s)) sp += s.substr(i + 1, sz(s) - i - 1);

        for (int j = 0; j <= sz(sp); j++) {
            string t;
            t += sp.substr(0, j);
            t += s[i];
            if (j < sz(sp)) t += sp.substr(j, sz(sp) - j);

            if (is_correct(t)) {
                cout << t << '\n';
                exit(0);
            }
        }
    }

    cout << "Impossible\n";
}
