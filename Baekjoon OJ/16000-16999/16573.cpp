#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

string s;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;

    int cnt0 = 0, cnt1 = 0;
    for (auto &i : s) {
        if (i == '0') cnt0++;
        else cnt1++;
    }    

    if (cnt0 < cnt1) {
        for (int i = 0; i < sz(s); i++) cout << 0;
    } else if (cnt0 > cnt1) {
        for (int i = 0; i < sz(s); i++) cout << 1;
    } else {
        
    }
}
