#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

string encode(int n, string s) {
    int cnt0{}, cnt1{};
    for (char c : s) cnt0 += c == '0', cnt1 += c == '1';

    if (!cnt0 || !cnt1) {
        return s;
    } else {
        string ret = s;
        ret[0] = '2';
        for (int i = 0; i + 1 < sz(s); i++) {
            if (s[i] == s[i + 1]) ret[i + 1] = '2';
            else break;
        }
        return ret;
    }

    // } else if (n == 2) {
    //     return "2" + string{s.begin() + 1, s.end()};
    // } else if (n == 3) {
    //     return "2" + (s[0] == s[1] ? "2" : string(1, s[1])) + string{s.begin() + 2, s.end()};
    // } else if (n == 4) {
        
    // } else {
    //     const int hs = (s[0] - '0') * 4 + (s[1] - '0') * 2 + (s[2] - '0');

    //     string ret;
    //     ret += '2';
    //     ret += (char)(hs / 3 + '0');
    //     ret += (char)(hs % 3 + '0');
    //     ret += string{s.begin() + 3, s.end()};
    //     return ret;
    // }
}

string decode(int n, string s) {
    int cnt2{};
    for (char c : s) cnt2 += c == '2';

    if (!cnt2) {
        return s;
    } else {
        vector<int> idx2;
        for (int i = 0; i < n; i++) {
            if (s[i] == '2') idx2.push_back(i);
        }

        char tgt{};
        if (sz(idx2) == 1) {
            // cout << s[idx2[0]] << '\n';
            // cout << s[(idx2[0] + 1) % n] << '\n';
            tgt = !(s[(idx2[0] + 1) % n] - '0') + '0';
            const int mid = idx2[0];
            s = s.substr(mid, sz(s) - mid) + s.substr(0, mid);
        } else {
            for (int i = 0; i < sz(idx2); i++) {
                if ((idx2[(i + 1) % sz(idx2)] - idx2[i] + n) % n != 1) {
                    const int mid = idx2[(i + 1) % sz(idx2)];
                    tgt = !(s[(idx2[i] + 1) % n] - '0') + '0';
                    s = s.substr(mid, sz(s) - mid) + s.substr(0, mid);
                    break;
                }
            }
        }
        
        string ret = s;
        for (char &c : ret) if (c == '2') c = tgt;

        return ret;
    }
    // } else if (n == 2) {
    //     return (s[1] == '0' ? "1" : "0") + string{s.begin() + 1, s.end()};
    // } else if (n == 3) {
    //     vector<int> idx2;
    //     for (int i = 0; i < n; i++) {
    //         if (s[i] == '2') idx2.push_back(i);
    //     }

    //     if (sz(idx2) == 1) {
    //         const int mid = idx2[0];
    //         s = s.substr(mid, sz(s) - mid) + s.substr(0, mid);
    //     } else if (sz(idx2) == 2) {
    //         const int mid = (idx2[1] - idx2[0] <= 1 ? idx2[0] : idx2[1]);
    //         s = s.substr(mid, sz(s) - mid) + s.substr(0, mid);
    //     } else assert(0);

    //     auto ret = s;
    //     if (s[1] != '2') ret[0] = !(s[1] - '0') + '0';
    //     else ret[0] = ret[1] = !(s[2] - '0') + '0';
    //     return ret;
    // } else if (n == 4) {
    //     // TODO
    // } else {
    //     vector<int> idx2;
    //     for (int i = 0; i < n; i++) {
    //         if (s[i] == '2') idx2.push_back(i);
    //     }

    //     if (sz(idx2) == 1) {
    //         const int mid = idx2[0];
    //         s = s.substr(mid, sz(s) - mid) + s.substr(0, mid);
    //     } else if (sz(idx2) == 2) {
    //         const int mid = (idx2[1] - idx2[0] <= 2 ? idx2[0] : idx2[1]);
    //         s = s.substr(mid, sz(s) - mid) + s.substr(0, mid);
    //     } else assert(0);

    //     const int hs = (s[1] - '0') * 3 + (s[2] - '0');

    //     string ret;
    //     ret += (char)(hs / 4 + '0');
    //     ret += (char)(hs % 4 / 2 + '0');
    //     ret += (char)(hs % 2 + '0');
    //     ret += string{s.begin() + 3, s.end()};
    //     return ret;
    // }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // TEST
    // mt19937 mt(time(NULL));
    // uniform_int_distribution<int> rng(0, 1'262'316);
    // for (int i = 0; i < 101010; i++) {
    //     const int n = 10;
    //     string s;
    //     while (sz(s) < n) s.push_back(rng(mt) % 2 + '0');

    //     string tmp = encode(n, s);
    //     const int mid = rng(mt) % sz(tmp);
    //     tmp = tmp.substr(mid, sz(tmp) - mid) + tmp.substr(0, mid);

    //     string t = decode(n, tmp);

    //     // cout << s << ' ' << tmp << ' ' << t << '\n';
    //     if (s != t) {
    //         cout << s << '\n' << tmp << '\n' << t << '\n';
    //         assert(0);
    //     }
    // }

    int n;
    string op, s;
    cin >> op >> n >> s;

    if (op == "Encode") {
        cout << encode(n, s) << '\n';
    } else {
        cout << decode(n, s) << '\n';
    }
}
