#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

int n, x;

int query(int i, int j) {
    cout << i << ' ' << j << '\n';
    cout.flush();

    int ret; cin >> ret;
    if (ret == 1) exit(0);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n >> x;

    for (int i = 1; i <= n; i++) {
        const int y = x;
        for (int cnt = 0; cnt < n; cnt++) {
            x = query(i, 1);
            if (x == y + 1) break;
        }
    }

    assert(x == n);

    x = query(1, 1);
    assert(x == n - 1);

    vector<int> jumps(n + 1);
    for (int i = 2; i <= n; i++) {
        int mx = 0;
        for (int j = 1; j <= n; j++) {
            x = query(i, 1);
            if (mx < x) {
                mx = x;
                jumps[i] = j;
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        x = query(i, jumps[i] + 1);
    }
}
