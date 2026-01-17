#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s;
        cin >> n >> s;

        int stk1 = 0, stk2 = 0;
        for (int i = 0; i + 1 < sz(s); i++) {
            if (s[i] == ')' && s[i + 1] == '(') {
                stk1++;
                for (int j = i + 2; j < sz(s); j++) {
                    if (s[j] == '(') {
                        stk2++;
                    } else {
                        if (stk1) stk1--;
                        else stk2--;
                    }
                }
                break;
            } else if (s[i] == '(') {
                stk1++;
            } else if (s[i] == ')') {
                stk1--;
            }
        }

        if (stk1) cout << -1 << '\n';
        else cout << n - stk2 * 2 << '\n';
    }
}
