#include <bits/stdc++.h>
using namespace std;

int a[11], cnt[11];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 1; i <= 6; i++) cin >> a[i];

    // 6
    int ans = a[6];
    a[6] = 0;
    // 5
    ans += a[5];
    cnt[1] += 11 * a[5];
    a[5] = 0;
    // 4
    ans += a[4];
    cnt[2] += 5 * a[4];
    a[4] = 0;
    // 3
    ans += (a[3] + 3) / 4;
    if (a[3] % 4 == 1) cnt[1] += 7, cnt[2] += 5;
    if (a[3] % 4 == 2) cnt[1] += 6, cnt[2] += 3;
    if (a[3] % 4 == 3) cnt[1] += 5, cnt[2] += 1;
    // 2
    int tmp = min(a[2], cnt[2]);
    a[2] -= tmp, cnt[2] -= tmp;
    cnt[1] += 4 * cnt[2];
    ans += (a[2] + 8) / 9;
    if (a[2] % 9) cnt[1] += 36 - 4 * (a[2] % 9);
    // 1
    tmp = min(a[1], cnt[1]);
    a[1] -= tmp, cnt[1] -= tmp;
    ans += (a[1] + 35) / 36;
    
    cout << ans;
}