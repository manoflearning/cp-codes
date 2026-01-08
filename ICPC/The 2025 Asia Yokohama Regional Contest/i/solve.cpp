#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()

bool who() {
    int a = 0, b = 0;
    int n; cin >> n;
    string s; cin >> s;
    
    vector<char> cand;
    int l = 0;
    while(l < n && s[l] == '.') l++;
    if(l == 1) {
        if(s[l] == 'a') b++;
        else a++;
    }
    else if(l > 1 && s[l] != '.') cand.push_back(s[l]);

    int r = n - 1;
    while(r >= 0 && s[r] == '.') r--;
    if(r == n - 2) {
        if(s[r] == 'a') b++;
        else a++;
    }
    else if(r < n - 2 && s[r] != '.') cand.push_back(s[r]);

    if(sz(cand) == 2) {
        if(cand[0] == 'a' && cand[1] == 'a') b++;
        if(cand[0] == 'b' && cand[1] == 'b') a++;
    }
    else if(sz(cand) == 1) {
        if(cand[0] == 'b') a++;
    }


    n = r - l + 1;
    s = s.substr(l, n);
    
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j + 1 < n && s[j + 1] == '.') j++;

        if(j - i > 0 && s[i] == s[j + 1]) {
            if(s[i] == 'a') b++;
            else if(s[i] == 'b') a++;
        }
        i = j;
    }
    return (a >= b + 1);
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cout << (who() ? "alice" : "bob") << '\n';
    }
}