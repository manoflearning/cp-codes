#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int n, k;
ll m;

struct Node { ll p, c; };
vector<Node> a;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k >> m;
    a.resize(n);
    for (auto& i : a)
        cin >> i.p >> i.c;

    sort(a.begin(), a.end(), [&](const Node& u, const Node& v) {
        if (u.c ^ v.c) return u.c < v.c;
        return u.p < v.p;
    });

    priority_queue<pll, vector<pll>, greater<pll>> pq;

    int ans = 0;
    ll sum = 0;
    for (auto& i : a) {
        if (k > 0) {
            if (sum + i.c <= m) {
                sum += i.c;
                pq.push({ i.p, i.c });
                k--, ans++;
            }
        }
        else {
            ll res1 = sum + i.p, res2 = sum + i.c + pq.top().fr - pq.top().sc;
            if (res1 <= res2 && res1 <= m) {
                sum = res1;
                ans++;
            }
            if (res1 > res2 && res2 <= m) {
                sum = res2;
                pq.pop();
                pq.push({ i.p, i.c });
                ans++;
            }
        }
    }

    cout << ans;

    return 0;
}