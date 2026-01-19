#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

bool valid(const vector<int> &b, const vector<int> &ans2) {
    int st = 0;
    for (int l : ans2) {
        if (l & 1) return 0;
        for (int i = st; i < st + l / 2; i++) {
            if (b[i] != b[i + l / 2]) return 0;
        }
        st += l;
    }
    if (st != sz(b)) return 0;
    return 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    constexpr int TC = 100;
    constexpr int N = 100;
    
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rng(1, N);

    cout << TC << '\n';
    for (int tc = 0; tc < TC; tc++) {
        cout << N << '\n';

        vector<int> arr;

        while (sz(arr) < N) {
            int x = rng(mt);
            arr.push_back(x);
            arr.push_back(x);
        }
        shuffle(all(arr), mt);

        for (auto &i : arr) cout << i << ' ';
        cout << '\n';
    }
}
