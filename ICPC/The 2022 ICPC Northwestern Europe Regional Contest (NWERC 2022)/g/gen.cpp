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
    uniform_int_distribution<int> bitgen(0, 1), ngen(3, 10);

    for (int tc = 0; tc < 100; tc++) {
        const int n = ngen(mt);
        for (int i = 0; i < n; i++) {
            cout << bitgen(mt);
        }
        cout << '\n';
        cout << "answer is: " << n << '\n';
        cout << '\n';
    }
}
