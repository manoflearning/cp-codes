#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n;
vector<int> a, b;

int pmn[1010101], pmn2[1010101];
int smn[1010101], smn2[1010101];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n + 2);
    b.resize(n + 2);

    a[0] = b[0] = 0;
    for (int i = 0; i < n; i++) cin >> a[i + 1];
    for (int i = 0; i < n; i++) cin >> b[i + 1];
    a[n + 1] = b[n + 1] = INF;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 1; i <= n; i++) 
        pmn[i] = max(pmn[i - 1], abs(a[i] - b[i]));
    for (int i = n; i >= 1; i--)
        smn[i] = max(smn[i + 1], abs(a[i] - b[i]));

    for (int i = 1; i < n; i++) {
        pmn2[i] = max(pmn2[i - 1], abs(a[i] - b[i + 1]));
        pmn2[i] = min(pmn2[i], pmn[i]);
    }

    for (int i = n; i > 1; i--) {
        smn2[i] = max(smn2[i + 1], abs(a[i] - b[i - 1]));
        smn2[i] = min(smn2[i], smn[i]);
    }

    int mn = 1e9 + 7, ans = -1;
    for (int i = 1; i <= n; i++) {
        int res = 1e9 + 7;
        res = min(res, max(pmn[i - 1], smn[i + 1]));
        res = min(res, max(pmn[i - 1], smn2[i + 1]));
        res = min(res, max(pmn2[i - 1], smn[i + 1]));

        if (res < mn) {
            mn = res, ans = a[i];
        }
    }

    cout << ans;

    return 0;
}