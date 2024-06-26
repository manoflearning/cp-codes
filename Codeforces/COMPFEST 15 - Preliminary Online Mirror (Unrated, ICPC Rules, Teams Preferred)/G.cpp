#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 202020;

struct Node {
    int r, x;
    bool operator<(const Node& rhs) const {
        return r > rhs.r;
    }
};

int n, a[MAXN], d[MAXN];
vector<Node> arr[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> d[i];

    vector<Node> ord;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        int l = max(1, i - d[i]), r = min(n, i + d[i]);
        arr[l].push_back({ r, a[i] });
    }

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;

        int isValid = 1;

        priority_queue<Node> pq;
        for (int i = 1; i <= n; i++) {
            for (auto& j : arr[i]) pq.push(j);

            int cnt = mid;
            while (!pq.empty() && cnt > 0) {
                if (pq.top().r < i) { isValid = 0; break; }
                if (pq.top().x <= cnt) {
                    cnt -= pq.top().x;
                    pq.pop();
                }
                else {
                    Node v = pq.top();
                    pq.pop();
                    v.x -= cnt;
                    cnt = 0;
                    pq.push(v);
                }
            }

            if (!isValid) break;
        }

        isValid &= pq.empty();

        if (isValid) r = mid;
        else l = mid + 1;
    }

    cout << l << '\n';
}