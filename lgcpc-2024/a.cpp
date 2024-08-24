#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, p;
string s;
int matches[55];

string f(int l, int r) {
    if (l == r) return string(1, s[l]);
    if (l > r) return "";

    vector<string> stk1;
    vector<char> stk2;

    string t;
    for (int i = l; i <= r; i++) {
        if (s[i] == '(') {
            t = "(" + f(i + 1, matches[i] - 1) + ")";
            i = matches[i];
            continue;
        }

        assert(s[i] != ')');

        if ('0' <= s[i] && s[i] <= '9') {
            t.push_back(s[i]);
        }
        if (s[i] == '*' || s[i] == '+') {
            stk1.push_back(t);
            t.clear();
            stk2.push_back(s[i]);
        }
    }
    stk1.push_back(t);
    stk2.push_back('+');

    string ret;
    for (int i = 0; i < sz(stk1); i++) {
        if (stk2[i] == '*' && (i == 0 || stk2[i - 1] == '+')) {
            ret += "(";
        }
        ret += stk1[i];
        if (stk2[i] == '+' && (i > 0 && stk2[i - 1] == '*')) {
            ret += ")";
        }
        if (i + 1 < sz(stk2)) ret += stk2[i];
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> p;

    cin >> s;

    stack<int> stk;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '(') stk.push(i);
        if (s[i] == ')') {
            matches[stk.top()] = i;
            stk.pop();
        }
    }

    string ans = f(0, sz(s) - 1);
    cout << sz(ans) << '\n' << ans;
}
