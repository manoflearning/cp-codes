#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, d[1010101];
int dp[1010101];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i];

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;

        struct Node {
            int x, h, loc;
            bool operator<=(const Node& rhs) const {
                if (x == rhs.x && h == rhs.h) return 1;

                if (x ^ rhs.x) return x < rhs.x;
                return h > rhs.h;
            }
        };
        
        deque<Node> dq;
        dq.push_back({ 0, d[1], 1 });

        for (int i = 2; i <= n; i++) {
            if (dq.front().loc == i - k - 1) dq.pop_front();

            int x = dq.front().x + (dq.front().h <= d[i]);
            if (i == n) {
                cout << x << '\n';
                break;
            }

            Node v = { x, d[i], i };
            while (sz(dq) && v <= dq.back()) dq.pop_back();
            dq.push_back(v);
        }
    }

    return 0;
}