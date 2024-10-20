#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 1010101;

int n;
string s;
int psum[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        psum[i + 1] = (s[i] == 'S') + psum[i];
    }

    for (int i = 1; i <= n; i++) {
        int now = 0, ans = 0;
        while (psum[now] < i && i - psum[now] <= n - now) {
            now = now + i - psum[now];
            ans++;
        }
        cout << ans << ' ';
    }
}