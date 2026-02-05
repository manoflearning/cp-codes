#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const vector<int> DIGITS = {
    119,
    96,
    62,
    124,
    105,
    93,
    95,
    100,
    127,
    125,
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<string> s(n);
    for (auto &i : s) cin >> i;

    for (const string &i : s) {
        int good{}, bad{};
        for (int j = 0; j < 7; j++) {
            if (i[j] == 'G') good += (1 << j);
            else if (i[j] == '+' || i[j] == '-') bad += (1 << j);
        }

        int cnt = 0, opt = -1;
        for (int i = 0; i < 10; i++) {
            if ((DIGITS[i] & good) == good && ((DIGITS[i] - good) & bad) == (DIGITS[i] - good)) {
                cnt++;
                opt = i;
            }
        }

        if (cnt == 1) cout << opt;
        else cout << "*";
    }
}
