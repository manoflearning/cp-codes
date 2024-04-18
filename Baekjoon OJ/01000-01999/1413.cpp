#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n = 0, m = 0; 
ll s[21][21];

ll gcd(ll a, ll b) {
   return b ? gcd(b, a % b) : a;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    scanf("%d %d" , &n, &m);
   
    s[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            s[i][j] = (i - 1) * s[i - 1][j] + s[i - 1][j - 1];
   
    for (int i = 1; i <= n; i++) s[n][i] += s[n][i - 1];
    ll G = gcd(s[n][m] , s[n][n]);
   
    printf("%lld/%lld" , s[n][m] / G , s[n][n] / G);
}