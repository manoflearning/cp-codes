#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int w, n;
int a[5050];
int cnt[808080];
bool ans = false;

void input() {
    cin >> w >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void solve() { // O(n^2)
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cnt[a[i] + a[j]]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cnt[a[i] + a[j]]--;
        }

        for (int j = 1; j < i; j++) {
            if (w - a[i] - a[j] >= 0 && cnt[w - a[i] - a[j]]) ans = true;
        }
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

    solve();

    cout << (ans ? "YES" : "NO");
}