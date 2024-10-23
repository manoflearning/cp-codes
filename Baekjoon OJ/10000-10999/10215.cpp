#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int cy[] = {1, 1, 2, 2};
const int cx[] = {1, 2, 2, 1};
const int coy[] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 3, 3};
const int cox[] = {0, 1, 2, 3, 0, 3, 0, 3, 0, 1, 2, 3};

int n;
vector<char> a;
vector<string> en;
map<vector<string>, double> mp[22];

void init() {
    a.clear();
    en.clear();
    for (int i = 0; i < 22; i++) mp[i].clear();
}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
    en.resize(4);
    for (auto& i : en) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        // base case
        mp[0][{
            "EEEE",
            "EEEE",
            "EEEE",
            "EEEE"
        }] = 1.0;

        // inductive step
        for (int i = 0; i < n; i++) {
            for (auto& [prv, prob] : mp[i]) {
                if (a[i] == 'W' || a[i] == 'G') {
                    int empty_cnt = 0;
                    for (int d = 0; d < 4; d++) {
                        empty_cnt += (prv[cy[d]][cx[d]] == 'E');
                    }

                    if (empty_cnt == 0) {
                        ll cnt = 0;
                        for (int d = 0; d < 12; d++) {
                            if (prv[coy[d]][cox[d]] == 'E') cnt++;
                        }
                        for (int d = 0; d < 12; d++) {
                            if (prv[coy[d]][cox[d]] == 'E') {
                                auto now = prv;
                                now[coy[d]][cox[d]] = a[i];
                                mp[i + 1][now] += prob / cnt;
                            }
                        }
                    } else if (empty_cnt == 3) {
                        for (int d = 0; d < 4; d++) {
                            if (prv[cy[d]][cx[d]] != 'E') {
                                auto now = prv;
                                now[cy[(d + 2) % 4]][cx[(d + 2) % 4]] = a[i];
                                mp[i + 1][now] += prob;
                                break;
                            }
                        }
                    } else if (empty_cnt == 1 || empty_cnt == 2 || empty_cnt == 4) {
                        for (int d = 0; d < 4; d++) {
                            if (prv[cy[d]][cx[d]] == 'E') {
                                auto now = prv;
                                now[cy[d]][cx[d]] = a[i];
                                mp[i + 1][now] += prob / empty_cnt;
                            }
                        }
                    }
                } else {
                    if (a[i] == 'L') {
                        vector<string> now(4);
                        for (int y = 0; y < 4; y++) {
                            string t;
                            for (int x = 0; x < 4; x++) {
                                if (prv[y][x] != 'E') t.push_back(prv[y][x]);
                            }
                            while (sz(t) < 4) t.push_back('E');
                            now[y] = t;
                        }
                        mp[i + 1][now] += prob;
                    } else if (a[i] == 'R') {
                        vector<string> now(4);
                        for (int y = 0; y < 4; y++) {
                            string t;
                            for (int x = 3; x >= 0; x--) {
                                if (prv[y][x] != 'E') t.push_back(prv[y][x]);
                            }
                            while (sz(t) < 4) t.push_back('E');
                            reverse(all(t));
                            now[y] = t;
                        }
                        mp[i + 1][now] += prob;
                    } else if (a[i] == 'T') {
                        vector<string> now(4, string(4, 'E'));
                        for (int x = 0; x < 4; x++) {
                            string t;
                            for (int y = 0; y < 4; y++) {
                                if (prv[y][x] != 'E') t.push_back(prv[y][x]);
                            }
                            while (sz(t) < 4) t.push_back('E');
                            for (int y = 0; y < 4; y++) now[y][x] = t[y];
                        }
                        mp[i + 1][now] += prob;
                    } else if (a[i] == 'B') {
                        vector<string> now(4, string(4, 'E'));
                        for (int x = 0; x < 4; x++) {
                            string t;
                            for (int y = 3; y >= 0; y--) {
                                if (prv[y][x] != 'E') t.push_back(prv[y][x]);
                            }
                            while (sz(t) < 4) t.push_back('E');
                            reverse(all(t));
                            for (int y = 0; y < 4; y++) now[y][x] = t[y];
                        }
                        mp[i + 1][now] += prob;
                    }
                }
            }   
        }
    
        cout << fixed;
        cout.precision(8);
        cout << mp[n][en] << '\n';
    }
}
