#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif
    
    vector<int> a(6), b(6);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;

    int awin = 0, all = 36;
    for (auto& i : a) {
        for (auto& j : b) {
            if (i > j) awin++;
        }
    }

    int g = gcd(awin, all);

    cout << awin / g << '/' << all / g;

    return 0;
}