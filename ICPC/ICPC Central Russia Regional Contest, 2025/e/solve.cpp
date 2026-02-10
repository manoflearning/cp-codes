#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// void f(int l, int r, bool x, string &s) {
//     for (int i = l; i < r; i++) {

//     }
// }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    string s; cin >> s;
    s = "+(" + s + ")";

    vector<int> stk;
    int cnt_neg = 0;
    int last_sign_idx = 0;
    for (int i = 1; i < sz(s); i++) {
        if (s[i] == '+' || s[i] == '-') {
            if (cnt_neg == 0) s[i] = '-';
            else s[i] = '+';
            last_sign_idx = i;
        } else if (s[i] == '(') {
            stk.push_back(last_sign_idx);
            if (s[last_sign_idx] == '-') cnt_neg++;
        } else if (s[i] == ')') {
            if (s[stk.back()] == '-') cnt_neg--;
            stk.pop_back();
        }
    }
    assert(stk.empty());

    const string ans{s.begin() + 2, s.end() - 1};
    cout << ans << '\n';
}
