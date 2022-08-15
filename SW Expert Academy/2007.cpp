#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

string s;

bool isMatched(int st, int len) {
    for (int i = 0; i < min(i + len, sz(s) - st); i++) {
        if (s[i] != s[i + st]) return 0;
    }
    return 1;
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << '#' << tt << ' ';

        cin >> s;
        for (int len = 1; len <= sz(s); len++) {
            int bit = 1;
            for (int i = len; i < sz(s); i += len) {
                if (!isMatched(i, len)) { bit = 0; break; }
            }

            if (bit) {
                cout << len << '\n';
                break;
            }
        }
    }

    return 0;
}