#include <bits/stdc++.h>
using namespace std;

int n, m;
int p[10];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= 8; i++) cin >> p[i];

    if ((n == 1 && m == 2) || (n == 2 && m == 1)) cout << "ChongChong";
    else cout << "GomGom";
}