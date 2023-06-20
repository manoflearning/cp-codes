// note
// the minimum number of steps를 구하는 것이므로 -> 파마메트릭 서치?

#include <bits/stdc++.h>
using namespace std;

int r, s, p;
int a[1010101];

void input() {
    cin >> r >> s >> p;
    for (int i = 0; i < p; i++) {
        int y, x;
        cin >> y >> x;
        x = (x <= s ? s - x + 1 : x - s);
        a[x + (r - y + 1)]++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    int ans = 0;
    for (int i = 1; i < 1010101; i++) {
        if (a[i] == 0) continue;
        ans = max(ans, i);
        a[i + 1] += a[i] - 1;
    }

    cout << ans;
}