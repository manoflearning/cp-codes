#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

vector<int> a;

void init() {
    a.clear();
}

void input() {
    string s;
    getline(cin, s);
    if (cin.eof()) exit(0);
    s.push_back(' ');
    string t;
    for (auto& i : s) {
        if ('0' <= i && i <= '9') {
            t.push_back(i);
        } else {
            if (!t.empty()) {
                a.push_back(stoi(t));
                t.clear();
            }
        }
    }
}

void no() {
    cout << "fail\n";
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        init();

        input();

        int sum = 0;
        for (auto& i : a) sum += i;

        if ((sum & 1) || sum > sz(a) * (sz(a) - 1)) no();
        else {
            vector<int> ord(sz(a));
            iota(all(ord), 0);

            sort(all(ord), [&](int p1, int p2) {
                return a[p1] > a[p2];
            });

            vector<vector<bool>> ans(sz(a), vector<bool>(sz(a)));
            for (int i = 0; i < sz(ord); i++) {
                int u = ord[i];

                for (int j = i + 1; j < sz(ord) && a[u] > 0; j++) {
                    int v = ord[j];
                    if (a[v] > 0) {
                        a[u]--, a[v]--;
                        ans[u][v] = ans[v][u] = 1;
                    }
                }

                sort(ord.begin() + i + 1, ord.end(), [&](int p1, int p2) {
                    return a[p1] > a[p2];
                });
            }
            
            bool is_valid = 1;
            for (int i = 0; i < sz(a); i++)
                if (a[i] > 0) is_valid = 0;

            if (is_valid) {
                for (int i = 0; i < sz(a); i++) {
                    for (int j = 0; j < sz(a); j++) {
                        cout << ans[i][j] << ' ';
                    }
                    cout << '\n';
                }
            } else no();
        }

        cout << '\n';
    }
}