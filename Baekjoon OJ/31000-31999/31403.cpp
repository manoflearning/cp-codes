#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;

    cout << a + b - c << '\n';
    cout << stoi(to_string(a) + to_string(b)) - c;
}