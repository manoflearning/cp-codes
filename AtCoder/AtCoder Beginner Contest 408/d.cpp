#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

struct Node {
    int c0; // no interval
    int c1; // one interval
    int cl; // one interval with leftmost value = 1
    int cr; // one interval with rightmost value = 1
    int call; // all value = 1
    Node operator+(const Node &rhs) const {
        Node ret;
        ret.c0 = c0 + rhs.c0;
        ret.c1 = min({c1 + rhs.c0, c0 + rhs.c1, cr + rhs.cl});
        ret.cl = min({cl + rhs.c0, call + rhs.c1});
        ret.cr = min({cr + rhs.call, c0 + rhs.cr});
        ret.call = call + rhs.call;
        return ret;
    }
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        string s; cin >> s;

        Node acc;
        for (int i = 0; i < n; i++) {
            Node now;
            if (s[i] == '1') now = {1, 0, 0, 0, 0};
            else now = {0, 1, 1, 1, 1};

            if (i == 0) acc = now;
            else acc = acc + now;

            // cout << i << '\n';
            // cout << "c0: " << acc.c0 << '\n';
            // cout << "c1: " << acc.c1 << '\n';
            // cout << "cl: " << acc.cl << '\n';
            // cout << "cr: " << acc.cr << '\n';
            // cout << "call: " << acc.call << '\n';
            // cout << '\n';
        }

        cout << min(acc.c0, acc.c1) << '\n';
    }
}
