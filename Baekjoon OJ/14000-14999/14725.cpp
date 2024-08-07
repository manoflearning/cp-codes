#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
vector<vector<string>> a;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        int cnt; cin >> cnt;
        i.resize(cnt);
        for (auto& j : i) cin >> j;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(a.begin(), a.end());

    for (int i = 0; i < sz(a[0]); i++) {
        for (int j = 0; j < i; j++) cout << "--";
        cout << a[0][i] << '\n';
    }

    for (int i = 1; i < n; i++) {
        bool isSame = true;
        for (int j = 0; j < sz(a[i]); j++) {
            if (isSame && a[i][j] == a[i - 1][j]) continue;
            isSame = false;
            for (int k = 0; k < j; k++) cout << "--";
            cout << a[i][j] << '\n';
        }
    }
}