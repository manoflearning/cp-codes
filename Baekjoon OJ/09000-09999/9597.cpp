#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

unordered_map<string, int> words[10101];

unordered_map<string, int> mp_cnt;
map<int, set<string>> mp_string;

void add(const string& s, int add) {
    int& cnt = mp_cnt[s];

    auto it_string = mp_string.find(cnt);
    if (it_string != mp_string.end()) {
        it_string->second.erase(s);
        if (it_string->second.empty()) {
            mp_string.erase(cnt);
        }
    }

    cnt += add;
    mp_string[cnt].insert(s);
}
void del(const string& s, int add) {
    int& cnt = mp_cnt[s];

    auto it_string = mp_string.find(cnt);
    if (it_string != mp_string.end()) {
        it_string->second.erase(s);
        if (it_string->second.empty()) {
            mp_string.erase(cnt);
        }
    }

    cnt -= add;
    if (cnt > 0)
        mp_string[cnt].insert(s);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int day = 0;
    while (!cin.eof()) {
        string op;
        getline(cin, op);
        // if (cin.eof()) break;

        if (3 <= sz(op) && op[2] == 'e') {
            day++;
            while (1) {
                string s; cin >> s;
                if (s[0] == '<') break;
                if (sz(s) >= 4) words[day][s]++;
            }
            for (auto& i : words[day]) add(i.first, i.second);

            if (day > 7) {
                for (auto& i : words[day - 7]) del(i.first, i.second);
                words[day - 7].clear();
            }
        }

        if (3 <= sz(op) && op[2] == 'o') {
            string s = op.substr(5, sz(op) - 3);
            int n = stoi(s);

            cout << "<top " << n << ">\n";

            auto it = mp_string.end();
            it--;
            while (1) {
                n -= sz(it->second);
                for (auto& i : it->second) {
                    cout << i << ' ' << it->first << '\n';
                }
                if (n <= 0) break;

                assert(it != mp_string.begin());
                it--;
            }

            cout << "</top>\n";
        }
    }
}
