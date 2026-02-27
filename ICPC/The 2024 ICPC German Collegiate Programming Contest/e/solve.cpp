#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int f(int cnt0, int cnt1, int cnt2, bool is_odd, vector<vector<vector<vector<int>>>> &dp, const int n) {
    int &ret = dp[cnt0][cnt1][cnt2][is_odd];
    
    if (ret != -1) return ret;
    const int turn = (n - cnt0 - cnt1 - cnt2) & 1;
    if (!cnt0 && !cnt1 && !cnt2) return ret = turn ^ is_odd;

    ret = 0;
    if (cnt0 > 0 && !f(cnt0 - 1, cnt1,  cnt2, is_odd, dp, n)) ret = 1;
    if (cnt1 > 0 && !f(cnt0, cnt1 - 1,  cnt2, !is_odd, dp, n)) ret = 1;
    if (cnt2 > 0 && !f(cnt0, cnt1,  cnt2 - 1, false, dp, n)) ret = 1;

    return ret;
}

bool is_type0(char op, int x) { return (op == '+' && (~x & 1)) || (op == '*' && (x & 1)); }
bool is_type1(char op, int x) { return op == '+' && (x & 1); }
bool is_type2(char op, int x) { return op == '*' && (~x & 1); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    set<pair<char, int>> st0, st1, st2;
    int cnt0{}, cnt1{}, cnt2{};

    for (int i = 0; i < n; i++) {
        char op; int x;
        cin >> op >> x;

        if (is_type0(op, x)) {
            cnt0++;
            st0.insert({op, x});
        } else if (is_type1(op, x)) {
            cnt1++;
            st1.insert({op, x});
        } else if (is_type2(op, x)) {
            cnt2++;
            st2.insert({op, x});
        }
        else { assert(0); }
    }

    int x; cin >> x;
    bool is_odd = x & 1;

    vector<vector<vector<vector<int>>>> dp(
        cnt0 + 1, vector<vector<vector<int>>>(
            cnt1 + 1, vector<vector<int>>(
                cnt2 + 1, vector<int>(
                    2, -1
                )
            )
        )
    );

    auto me = [&](const int type_id) {
        if (type_id == 0) {
            assert(!st0.empty());

            auto it = st0.begin();
            cout << it->first << ' ' << it->second << '\n';
            cout.flush();

            cnt0--;
            st0.erase(it);
        } else if (type_id == 1) {
            assert(!st1.empty());

            auto it = st1.begin();
            cout << it->first << ' ' << it->second << '\n';
            cout.flush();

            cnt1--;
            st1.erase(it);
            is_odd = !is_odd;
        } else if (type_id == 2) {
            assert(!st2.empty());

            auto it = st2.begin();
            cout << it->first << ' ' << it->second << '\n';
            cout.flush();

            cnt2--;
            st2.erase(it);
            is_odd = false;
        } else { assert(0); }
    };

    auto you = [&]() {
        char op; int x;
        cin >> op >> x;
        if (is_type0(op, x)) { cnt0--, st0.erase({op, x}); }
        else if (is_type1(op, x)) { cnt1--, st1.erase({op, x}); is_odd = !is_odd; }
        else if (is_type2(op, x)) { cnt2--, st2.erase({op, x}); is_odd = false; }
        else { assert(0); }
    };

    const int res = f(cnt0, cnt1, cnt2, is_odd, dp, n);
    if (res) {
        cout << "me\n";
        cout.flush();
    } else {
        cout << "you\n";
        cout.flush();
        you();
    }
    
    while (cnt0 > 0 || cnt1 > 0 || cnt2 > 0) {
        if (cnt0 > 0 && !f(cnt0 - 1, cnt1,  cnt2, is_odd, dp, n)) {
            me(0);
        } else if (cnt1 > 0 && !f(cnt0, cnt1 - 1,  cnt2, !is_odd, dp, n)) {
            me(1);
        } else if (cnt2 > 0 && !f(cnt0, cnt1,  cnt2 - 1, false, dp, n)) {
            me(2);
        } else { assert(0); }

        if (cnt0 > 0 || cnt1 > 0 || cnt2 > 0) you();
    }
}
