#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 998'244'353;

int n;
vector<ll> p;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    p.resize(n);
    for (auto& i : p) cin >> i;
}