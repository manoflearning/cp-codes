#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 10101;

void f(vector<int>& a, vector<int>& b) {
    for (int i = 1; i < 10000; i++) {
        for (int x = 9; x >= 0; x--) {
            if ((a[0] * x * 2 + b[i]) % 10 == x) {
                a[i] = x;
                break;
            }
            
        }

        for (int j = 0; j <= i; j++) {
            b[i + j] += a[i] * a[j] * (j < i ? 2 : 1);
            b[i + j + 1] += b[i + j] / 10;
            b[i + j] %= 10;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> a5(MAXN << 1);
    vector<int> b5(MAXN << 1);

    a5[0] = 5;
    b5[0] = 5;
    b5[1] = 2;
    f(a5, b5);

    vector<int> a6(MAXN << 1);
    vector<int> b6(MAXN << 1);
    
    a6[0] = 6;
    b6[0] = 6;
    b6[1] = 3;
    f(a6, b6);

    for (int i = n - 1; i >= 0; i--) {
        if (a5[i] > a6[i]) { cout << 5; exit(0); }
        if (a5[i] < a6[i]) { cout << 6; exit(0); }
    }
}
