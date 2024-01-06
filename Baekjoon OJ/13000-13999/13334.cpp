#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, d;
vector<pii> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
        if (i.fr > i.sc) swap(i.fr, i.sc);
    }
    cin >> d;

    priority_queue<int, vector<int>, greater<int>> pq;
    sort(all(a), [&](const pii& p1, const pii& p2) {
        return p1.sc < p2.sc;
    });

    int ans = 0;
    for (int i = 0; i < n; i++) {
        pq.push(a[i].fr);
        while (!pq.empty() && pq.top() + d < a[i].sc) {
            pq.pop();
        }
        // cout << i << ' ' << a[i].fr << ' ' << a[i].sc << ' ' << sz(pq) << '\n';
        ans = max(ans, sz(pq));
    }

    cout << ans;
}