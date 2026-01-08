#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (x).size()

ll x;
string s;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);

    cin >> x;

    s=to_string(x);
    ll y=1;
    while(y<x) {
        string now=to_string(x-y)+to_string(y);
        if(sz(now)>sz(s)) s=now;
        else s=max(now, s);
        y*=10;
    }

    cout << s << '\n';
}