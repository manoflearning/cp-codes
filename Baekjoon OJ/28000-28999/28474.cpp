#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 51;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

ll F[MAX];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    F[1] = F[2] = 1;
    for (int i = 3; i < MAX; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }

    for (int i = 1; i < MAX; i++) {
        int cnt = 0;
        vector<int> arr;
        for (int j = 1; j < i; j++) {
            if (gcd(F[i], F[j]) == 1) {
                cnt++;
                arr.push_back(F[j]);
            }
        }

        cout << "for " << i << "th fibonacci:\t" << "answer is " << cnt << '\n';
        cout << i << "th fibonacci: \t" << F[i] << '\n';
        cout << "gcd with: \t\t\t";
        for (auto& j : arr) 
            cout << j << ' ';
        cout << "\n\n";
    }
}