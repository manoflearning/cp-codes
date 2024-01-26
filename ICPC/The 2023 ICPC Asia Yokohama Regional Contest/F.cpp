#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 505050;

int n, q;
map<int, int> mpR, mpC;
ll ans = 0, rowCnt, colCnt;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;

    ans = (ll)n * n;
    rowCnt = colCnt = n;

    for (int i = 0; i < q; i++) {
        string op; int x;
        cin >> op >> x;

        if (op == "ROW") {
            int b = (mpC[x] & 1);
            int bl = (mpC[x - 1] & 1), br = (mpC[x + 1] & 1);

            if (x > 1 && b == bl) {
                ans -= rowCnt;
                colCnt--;
            }
            if (x > 1 && b != bl) {
                ans += rowCnt;
                colCnt++;
            }
            if (x < n && b == br) {
                ans -= rowCnt;
                colCnt--;
            }
            if (x < n && b != br) {
                ans += rowCnt;
                colCnt++;
            }

            mpC[x]++;
        }
        if (op == "COLUMN") {
            int b = (mpR[x] & 1);
            int bl = (mpR[x - 1] & 1), br = (mpR[x + 1] & 1);

            if (x > 1 && b == bl) {
                ans -= colCnt;
                rowCnt--;
            }
            if (x > 1 && b != bl) {
                ans += colCnt;
                rowCnt++;
            }
            if (x < n && b == br) {
                ans -= colCnt;
                rowCnt--;
            }
            if (x < n && b != br) {
                ans += colCnt;
                rowCnt++;
            }

            mpR[x]++;
        }

        cout << ans << '\n';
    }
}