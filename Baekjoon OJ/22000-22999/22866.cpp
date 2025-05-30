#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

int n, a[101010];
int cnt[101010], l[101010], r[101010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 101010; i++)
        l[i] = r[i] = 1e9 + 7;

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i + 1];

    stack<pii> stk;
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && stk.top().fr <= a[i]) stk.pop();

        cnt[i] += stk.size();
        if (!stk.empty()) l[i] = stk.top().sc;

        stk.push({ a[i], i });
    }

    while (!stk.empty()) stk.pop();

    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && stk.top().fr <= a[i]) stk.pop();

        cnt[i] += stk.size();
        if (!stk.empty()) r[i] = stk.top().sc;

        stk.push({ a[i], i });
    }

    for (int i = 1; i <= n; i++) {
        cout << cnt[i] << ' ';
        if (cnt[i]) {
            if (abs(i - l[i]) <= abs(i - r[i])) cout << l[i];
            else cout << r[i];
        }
        cout << '\n';
    }

    return 0;
}