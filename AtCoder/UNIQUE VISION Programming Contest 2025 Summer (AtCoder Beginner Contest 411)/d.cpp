#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    vector<string> pc(n + 1);

    int server_id = 0;
    vector<int> pc_id(n + 1);
    iota(all(pc_id), 0);

    vector<int> prv(n + 1, -1);
    vector<string> t(n + 1, "");

    while (q--) {
        int op; cin >> op;

        if (op == 1) {
            int p; cin >> p;
            prv.push_back(pc_id[0]);
            t.push_back("");
            pc_id[p] = sz(prv) - 1;
        } else if (op == 2) {
            int p;
            string s;
            cin >> p >> s;
            
            prv.push_back(pc_id[p]);
            t.push_back(s);
            pc_id[p] = sz(prv) - 1;
        } else if (op == 3) {
            int p; cin >> p;
            
            prv.push_back(pc_id[p]);
            t.push_back("");
            pc_id[0] = sz(prv) - 1;
        }
    }

    stack<string> ans;
    int idx = pc_id[0];
    while (idx != -1) {
        ans.push(t[idx]);
        idx = prv[idx];
    }
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
}
