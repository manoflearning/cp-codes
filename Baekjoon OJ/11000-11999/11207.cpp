#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 10101;

int n;
vector<string> pos[MAXN], neg[MAXN];
vector<int> a[MAXN], b[MAXN];

int pw[252], nw[252];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int w; cin >> w;
        while (w--) {
            string s; cin >> s;
            if (s[0] == '+') pos[i].push_back(s.substr(1, sz(s) - 1));
            if (s[0] == '-') neg[i].push_back(s.substr(1, sz(s) - 1));
        }
    }
}

vector<string> cc;
void coor_comp() {
    cc.push_back("`");
    for (int i = 1; i <= n; i++) {
        for (auto& s : pos[i]) cc.push_back(s);
        for (auto& s : neg[i]) cc.push_back(s);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (int i = 1; i <= n; i++) {
        for (auto& s : pos[i]) {
            int x = lower_bound(all(cc), s) - cc.begin();
            a[i].push_back(x);
            pw[x]++;
        }
        for (auto& s : neg[i]) {
            int x = lower_bound(all(cc), s) - cc.begin();
            b[i].push_back(x);
            nw[x]++;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    coor_comp();

    srand(time(NULL));

    while (1) {
        vector<bool> is_pos(sz(cc)), vis(sz(cc));
        for (int i = 1; i <= n; i++) {
            
        }

        bool is_valid = 1;
        for (int i = 1; i <= n; i++) {
            int score = 0;
            for (auto& j : a[i]) 
                if (vis[j] && is_pos[j]) score++;
            for (auto& j : b[i])
                if (vis[j] && !is_pos[j]) score++;
            if (score < (sz(p[i]) + sz(q[i])) / 3 + 1) {
                is_valid = 0;
                break;
            }
        }

        if (!is_valid) continue;

        for (int i = 1; i < sz(cc); i++) {
            if (is_pos[i]) cout << cc[i] << '\n';
        }
        break;
    }
}
