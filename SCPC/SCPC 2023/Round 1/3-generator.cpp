#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int tc = 1;
    cout << tc << '\n';
    int n = 10'000;
    cout << n << '\n';

    int sum = n - 1;
    vector<int> a(n);

    for (int i = 0; i < 1000; i++)
        a[rand() % n] += rand() % 10;

    for (auto& i : a)
        cout << i << ' ';
}