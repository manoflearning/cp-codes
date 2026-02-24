#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i, i--;

    vector<int> stk1, stk2, res;

    auto op1_1 = [&](int x) {
        cout << "1\n";
        stk1.push_back(x);
    };

    auto op2_1 = [&]() {
        cout << "-1\n";
        res.push_back(stk1.back());
        stk1.pop_back();
    };

    auto op3_12 = [&]() {
        cout << "12\n";
        stk2.push_back(stk1.back());
        stk1.pop_back();
    };
    auto op3_21 = [&]() {
        cout << "21\n";
        stk1.push_back(stk2.back());
        stk2.pop_back();
    };

    for (const int x : a) {
        while (!stk1.empty() && stk1.back() < x) op3_12();
        op1_1(x);
        while (!stk2.empty()) op3_21();
    }
    while (!stk1.empty()) op2_1();

    assert(sz(res) == n);
    for (int i = 0; i < n; i++) {
        assert(res[i] == i);
    }
}