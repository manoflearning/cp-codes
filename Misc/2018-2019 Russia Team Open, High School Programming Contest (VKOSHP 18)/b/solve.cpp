#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<string> acc;

    string li;
    while (getline(cin, li)) {
        acc.push_back(li);
    }

    vector<string> ord_ref;
    vector<string> ord_bib;
    map<string, string> bib;

    bool is_phase_1 = 1;
    for (auto &s : acc) {
        if (s == "\\begin{thebibliography}{99}") {
            is_phase_1 = 0;
            continue;
        }
        if (s == "\\end{thebibliography}") break;

        for (int i = 0; i < sz(s); i++) {
            if (s[i] == '\\') {
                string t;
                bool get_t = 0;
                for (int j = i + 1; j < sz(s); j++) {
                    if (s[j] == '{') get_t = 1;
                    else if (s[j] == '}') {
                        get_t = 0;
                        i = j;
                        break;
                    } else if (get_t) {
                        t.push_back(s[j]);
                    }
                }

                if (is_phase_1) {
                    ord_ref.push_back(t);
                } else {
                    ord_bib.push_back(t);
                    bib[t] = s;
                }
            }
        }
    }

    if (ord_ref == ord_bib) {
        cout << "Correct\n";
    } else {
        cout << "Incorrect\n";
        cout << "\\begin{thebibliography}{99}\n";
        for (auto &i : ord_ref) {
            cout << bib[i] << '\n';
        }
        cout << "\\end{thebibliography}\n";
    }

    // DEBUG
    // for (auto & i : ord_ref) {
    //     cout << i << '\n';
    // }
}