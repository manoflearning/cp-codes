#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, k;

int msb(int x) {
    int ret = 0;
    for (; (1 << ret) <= x; ret++);
    return ret - 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;

    cout << "YES\n";
    if (k == (1 << n)) {
        for (int i = 0; i < (1 << n); i++) {
            cout << i << ' ';
        }
    }
    else {
        for (int i = 1; i < (1 << n); i++) {
            if ((1 << msb(i)) & k) cout << i << ' ';
        }
    }
}