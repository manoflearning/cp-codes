#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

char to_hex_char(int x) {
    if (x < 10) return '0' + x;
    else return (x - 10) + 'a';
}
string to_hex_string(int x) {
    string ret(4, '.');
    ret[0] = to_hex_char(x / (1 << 12));
    ret[1] = to_hex_char(x / (1 << 8) % (1 << 4));
    ret[2] = to_hex_char(x / (1 << 4) % (1 << 4));
    ret[3] = to_hex_char(x / (1 << 0) % (1 << 4));
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int x; cin >> x;

    constexpr int idx0 = 3;
    constexpr int idx1 = 7;

    vector<int> words(1 << 12);
    words[idx0] = 0, words[idx1] = 1;

    constexpr int ub = 64;

    auto set = [&](int idx, int a, int b, int c) {
        words[idx] = a;
        words[idx + 1] = b;
        words[idx + 2] = c;
    };

    for (int b = 0; b < 16; b++) {
        set(4 * b, (1 << 16) - (16 - b), 16 * (4 * b + 2) + 2, ub + 8 * b);

        const int pad_s = (x & (1 << b) ? 4 : 0);
        const int pad_f = (x & (1 << b) ? 0 : 4);

        if (b + 1 < 16) {
            set(ub + 8 * b + pad_s, 0, 0, 4 * (b + 1));
        } else {
            set(ub + 8 * b + pad_s, idx1, (1 << 16) - 16, (1 << 16) - 1);
        }

        set(ub + 8 * b + pad_f, idx0, (1 << 16) - 16, (1 << 16) - 1);
    }

    // DEBUG
    // for (int i = 0; i < 12 * 16; i++) {
    //     cout << words[i] << " \n"[i % 4 == 3];
    // }

    for (int i = 0; i < 12 * 16; i++) {
        cout << to_hex_string(words[i]) << " \n"[i % 4 == 3];
    }
}
