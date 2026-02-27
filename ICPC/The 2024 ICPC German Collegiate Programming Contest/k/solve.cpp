#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    string s, t;
    cin >> s >> t;

    int h{}, v{}, r{};
    for (char c : t) {
        h += (c == 'h');
        v += (c == 'v');
        r += (c == 'r');
    }
    h &= 1, v &= 1, r &= 1;

    string ans = s;
    if (h) {
        string tmp;
        for (char c : ans) {
            if (c == 'b') tmp.push_back('d');
            if (c == 'd') tmp.push_back('b');
            if (c == 'p') tmp.push_back('q');
            if (c == 'q') tmp.push_back('p');
        }
        reverse(all(tmp));
        ans = tmp;
    }
    if (v) {
        string tmp;
        for (char c : ans) {
            if (c == 'b') tmp.push_back('p');
            if (c == 'd') tmp.push_back('q');
            if (c == 'p') tmp.push_back('b');
            if (c == 'q') tmp.push_back('d');
        }
        ans = tmp;
    }
    if (r) {
        string tmp;
        for (char c : ans) {
            if (c == 'b') tmp.push_back('q');
            if (c == 'd') tmp.push_back('p');
            if (c == 'p') tmp.push_back('d');
            if (c == 'q') tmp.push_back('b');
        }
        reverse(all(tmp));
        ans = tmp;
    }

    cout << ans << '\n';
}
