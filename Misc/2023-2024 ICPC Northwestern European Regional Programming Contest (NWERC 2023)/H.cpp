#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Node {
    ll x, y;
    bool operator<(const Node &rhs) const {
        return x + y > rhs.x + rhs.y;
    }
};

int n;
priority_queue<Node> pq;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    if (n == 1) {
        ll x; cin >> x;
        cout << x;
        exit(0);
    }

    int cnt1 = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        if (x > 1) pq.push({x, 0});
        else cnt1++;
    }

    while (cnt1 >= 2) {
        cnt1 -= 2;
        pq.push({0, 2});
    }

    if (cnt1 == 1) {
        assert(!pq.empty());
        auto [x, y] = pq.top();
        pq.pop();
        pq.push({x, y + 1});
    }

    vector<Node> ans;
    while (!pq.empty()) {
        ans.push_back(pq.top());
        pq.pop();
    }
    
    string ans2;
    for (int i = 0; i < sz(ans); i++) {
        if (ans[i].y > 0) {
            ans2 += "(";
            // cout << '(';
            if (ans[i].x) {
                ans2 += to_string(ans[i].x);
                ans2 += "+";
                // cout << ans[i].x << '+';
            }
            while (ans[i].y--) {
                ans2 += "1";
                // cout << 1;
                if (ans[i].y) {
                    ans2 += "+";
                    // cout << '+';
                }
            }
            ans2 += ")";
            // cout << ')';
        } else {
            ans2 += to_string(ans[i].x);
        }
        if (i + 1 < sz(ans)) {
            ans2 += "*";
            // cout << '*';
        }
    }

    assert(sz(ans2) <= 1'000'000);
    cout << ans2;
}
