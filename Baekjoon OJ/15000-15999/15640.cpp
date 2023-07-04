#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n = 100, m = 2;
    vector<pair<int, int>> a;

    int en = 1;
    vector<int> vi(101);
    for (int st = 3; st <= 99; st += 3) {
        while (vi[en]) en++;
        a.push_back({ st, en });
        vi[st] = vi[en] = 1;
    }

    cout << n << ' ' << m << ' ' << a.size() << '\n';
    for (auto& i : a)
        cout << i.first << ' ' << i.second << '\n';
}