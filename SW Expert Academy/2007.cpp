#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

string s;

// 0부터 시작하는 길이 len의 부분문자열과 st부터 시작하는 길이 len의 부분문자열이 일치하면 1, 일치하지 않으면 0을 반환.
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
        // 1부터 문자열 최대 길이까지 패턴의 가능한 모든 길이를 완전탐색.
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