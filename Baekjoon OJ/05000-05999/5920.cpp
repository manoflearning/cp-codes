#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20202;

int n, a[5][MAXN];
int idx[5][MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < 5; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            idx[i][a[i][j]] = j;
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) ans.push_back(i);

    sort(ans.begin(), ans.end(), [&](const int p1, const int p2) {
        int cnt = 0;
        for (int i = 0; i < 5; i++) {
            if (idx[i][p1] < idx[i][p2]) cnt++;
        }
        return 3 <= cnt;
    });

    for (auto& i : ans)
        cout << i << '\n';
}