#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n; cin >> n;

        int ans = -1;

        int cnt5 = 0, cnt10 = 0;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;

            if (x == 500) {
                cnt5++;
            } else if (x == 1000) {
                if (cnt5 > 0) {
                    cnt5--; cnt10++;
                } else {
                    if (ans == -1) ans = i;
                }
            } else if (x == 5000) {
                if (cnt5 > 0 && cnt10 * 1000 + cnt5 * 500 >= 4500) {
                    int rem = 4500;
                    while (rem >= 1000 && cnt10 > 0) {
                        rem -= 1000;
                        cnt10--;
                    }
                    while (rem >= 500 && cnt5 > 0) {
                        rem -= 500;
                        cnt5--;
                    }
                } else {
                    if (ans == -1) ans = i;
                }
            } else {
                assert(0);
            }
        }
        if (ans == -1) ans = n;

        cout << "Case #" << tt << endl;
        cout << ans << endl;
    }
}
