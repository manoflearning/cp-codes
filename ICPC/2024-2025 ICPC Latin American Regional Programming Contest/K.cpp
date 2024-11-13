#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int K;
    string S;
    cin >> K >> S;

    if (K == 2) {
        int ans1 = 0;
        int ans2 = 0;
        for (int i = 0; i < sz(S); i++) {
            if ((S[i] == '0') != (i % 2 == 0)) ans1++;
            if ((S[i] == '0') != (i % 2 == 1)) ans2++;
        }

        if (ans1 <= ans2) {
            cout << ans1 << ' ';
            for (int i = 0; i < sz(S); i++) {
                cout << (i % 2 == 0 ? '0' : '1');
            }
        } else {
            cout << ans2 << ' ';
            for (int i = 0; i < sz(S); i++) {
                cout << (i % 2 == 0 ? '1' : '0');
            }
        }

        exit(0);
    }

    int ans = 0;

    int prv = 0;
    for (int i = 0; i < sz(S); i++) {
        if (i > 0 && S[i - 1] == S[i]) {
            prv++;
        } else prv = 1;

        if (prv >= K) {
            ans++;
            if (i + 1 < sz(S) && S[i] != S[i + 1]) {
                S[i - 1] = (S[i] == '0' ? '1' : '0');
            } else {
                S[i] = (S[i] == '0' ? '1' : '0');
            }
            prv = 1;
        }
    }

    cout << ans << ' ' << S;
}
