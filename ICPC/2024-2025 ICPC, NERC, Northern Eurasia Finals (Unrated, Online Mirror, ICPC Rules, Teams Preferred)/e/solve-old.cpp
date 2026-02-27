#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

bool is_valid_exp(const string &s) {
    int cnt = 0;
    string acc;
    for (int i = 0; i < sz(s); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            acc.push_back(s[i]);
        } else {
            if (/*i > 0 && */acc.empty()) return false;
            if (sz(acc) > 1 && acc[0] == '0') return false;
            if (sz(acc) > 10) return false;
            acc.clear();
        }
    }

    if (acc.empty()) return false;
    if (sz(acc) > 1 && acc[0] == '0') return false;
    if (sz(acc) > 10) return false;

    return true;
}

bool is_valid(const string &s) {
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '=') {
            // if (i == 0 || i + 1 == sz(s)) return false;

            bool yes = 1;
            yes &= is_valid_exp(s.substr(0, i));
            yes &= is_valid_exp(s.substr(i + 1, sz(s) - i - 1));
            return yes;
        }
    }

    assert(0);
}

bool is_correct(const string &s) {
    if (!is_valid(s)) return false;

    string acc;
    ll sum = 0;
    
    int sign{1};
    bool is_lhs = true;
    for (int i = 0; i < sz(s); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            acc.push_back(s[i]);
        } else {
            if (!acc.empty()) {
                sum += stoll(acc) * sign * (is_lhs ? +1 : -1);
                acc.clear();
            }

            if (s[i] == '=') is_lhs = false;
            else if (s[i] == '+') sign = +1;
            else if (s[i] == '-') sign = -1;
            else assert(0);
        }
    }

    if (!acc.empty()) {
        sum += stoll(acc) * sign * (is_lhs ? +1 : -1);
        acc.clear();
    }

    return (sum == 0);
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
