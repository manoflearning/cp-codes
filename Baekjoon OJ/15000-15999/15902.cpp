#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

int n;
vector<int> a, b;
vector<ll> arr;
ll dp[3030];

void input() {
    cin >> n;
    int cnt; cin >> cnt;
    a.resize(cnt);
    for (auto& i : a) cin >> i;
    cin >> cnt;
    b.resize(cnt);
    for (auto& i : b) cin >> i;
}

void splitBlock() {
    int ia = 0, ib = 0;
    while (ia < a.size() && ib < b.size()) {
        if (a[ia] == b[ib]) {
            ia++, ib++;
            continue;
        }
        if (a[ia] > b[ib] && a[ia] == b[ib] + b[ib + 1]) {
            arr.push_back(2);
            ia++, ib += 2;
            continue;
        }
        if (a[ia] < b[ib] && a[ia] + a[ia + 1] == b[ib]) {
            arr.push_back(2);
            ia += 2, ib++;
            continue;
        }

        if (a[ia] > b[ib] && a[ia] < b[ib] + b[ib + 1]) {
            ia++, ib += 2;
            int lena = 2, lenb = 3;
            while (a[ia] == 2 && b[ib] == 2) {
                lena += 2, lenb += 2;
                ia++, ib++;
            }
            if (a[ia] == 2) {
                lena += 2, lenb++;
                ia++, ib++;
            }
            else lena++, ia++;
            arr.push_back(lena);
            continue;
        }
        if (a[ia] < b[ib] && a[ia] + a[ia + 1] > b[ib]) {
            ia += 2, ib++;
            int lena = 3, lenb = 2;
            while (a[ia] == 2 && b[ib] == 2) {
                lena += 2, lenb += 2;
                ia++, ib++;
            }
            if (b[ib] == 2) {
                lena++, lenb += 2;
                ia++, ib++;
            }
            else lenb++, ib++;
            arr.push_back(lena);
            continue;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    splitBlock();

    
}