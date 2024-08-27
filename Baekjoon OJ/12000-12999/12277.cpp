#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const string NUMS1[] = {
    "",
    "",
    "double",
    "triple",
    "quadruple",
    "quintuple",
    "sextuple",
    "septuple",
    "octuple",
    "nonuple",
    "decuple",
    "",
};

const string NUMS2[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

void f(string& p, vector<string>& ans) {
    int cnt = 1;
    p.push_back('*');
    for (int i = 1; i < sz(p); i++) {
        if (p[i] != p[i - 1]) {
            if (2 <= cnt && cnt <= 10) ans.push_back(NUMS1[cnt]);
            if (1 <= cnt && cnt <= 10) {
                ans.push_back(NUMS2[p[i - 1] - '0']);
            }
            if (cnt == 11) {
                for (int j = 0; j < 11; j++) {
                    ans.push_back(NUMS2[p[i - 1] - '0']);
                }
            }

            cnt = 1;
        }
        else cnt++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";

        string s, t;
        cin >> s >> t;

        vector<int> div;

        string prv;
        t += '-';
        for (int i = 0; i < sz(t); i++) {
            if (t[i] == '-') {
                div.push_back(stoi(prv));
                prv.clear();
            }
            else prv += t[i];
        }

        for (int i = 1; i < sz(div); i++) {
            div[i] += div[i - 1];
        }
        
        vector<string> ans;
        for (int i = 0; i < sz(div); i++) {
            int l = (i == 0 ? 0 : div[i - 1]);
            int r = div[i];

            string p = s.substr(l, r - l);
            f(p, ans);
        }

        for (auto& i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
