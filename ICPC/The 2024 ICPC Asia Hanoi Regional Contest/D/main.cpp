#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 101010;
const int D = 59;

int n;
ll k;

bool vis[N];
int ans[N];

void f(int idx, ll rem) {
    if (rem == 1) {
        int j = 1;
        for (int i = idx; i < n; i++) {
            while (vis[j]) j++;

            ans[i] = j++;
        }
        return;
    }

    int cnt = 0;
    for (int x = 2; ; x++) {
        if (vis[x]) continue;

        cnt++;

        if (rem <= (1ll << cnt)) {
            vis[x] = 1;
            ans[idx] = x;

            f(idx + 1, rem - (1ll << (cnt - 1)));

            vis[x] = 0;
            break;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> k;

        f(0, k);

        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

// start with 1: 1 case
// start with 2: 1 case
// start with 3: 2 cases
// start with x: 2^(x - 2) cases