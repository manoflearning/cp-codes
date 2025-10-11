#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define sz(x) (int)(x).size()

string n;
vector<pii> ans;

void invalid() {
    cout << -1;
    exit(0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    if (sz(n) & 1) {
        invalid();
    }

    for (int i = 0; i + 1 < sz(n); i += 2) {
        int cnt = n[i] - '0';
        int val = n[i + 1] - '0';

        if (cnt == 0) {
            invalid();
        }

        if (!ans.empty()) {
            int cnt_prv = ans.back().first;
            int val_prv = ans.back().second;

            if (val == val_prv) {
                invalid();
            } else {
                ans.push_back({cnt, val});
            }
        } else {
            ans.push_back({cnt, val});
        }
    }

    if (ans.front().second == 0) {
        invalid();
    }

    for (auto i : ans) {
        while (i.first--) {
            cout << i.second;
        }
    }
}
