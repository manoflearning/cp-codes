#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

string s;

void init() {}
void input() { cin >> s; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (sz(s) == 1) {
            cout << 1 << '\n';
            continue;
        }

        string t;
        for (int i = (sz(s) + 1) / 2; i < sz(s); i++) {
            t.push_back(s[i]);
        }
        s.resize(sz(s) / 2);
    }
}