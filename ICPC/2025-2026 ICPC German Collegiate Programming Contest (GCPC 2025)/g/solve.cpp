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

    int cnt = 0;
    for (char i = '0'; i <= '9'; i++) {
        if (cnt == n) break;
        for (char j = 'A'; j <= 'Z'; j++) {
            if (cnt == n) break;
            for (char k = 'a'; k <= 'z'; k++) {
                if (cnt == n) break;
                for (char l = '!'; l <= '/'; l++) {
                    if (cnt == n) break;
                    cout << i << j << k << l << i << j << k << l << '\n';
                    cnt++;
                }
            }
        }
    }
}
