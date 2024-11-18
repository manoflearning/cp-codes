#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int P[] = {2, 2, 2, 269, 7487};

int n, a[101010];
map<int, int> mp;

vector<int> ans;

void print(const vector<int> &ans) {
    cout << sz(ans) << '\n';
    for (auto &i : ans) cout << i << ' ';
    exit(0);
}

void bt(int i) {
    if (i == 5) print(ans);

    int x = 1;
    for (int j = i; j <= 4; j++) {
        x *= P[j];

        if (mp[x] == 0) continue;

        mp[x]--;
        ans.push_back(x);
        bt(j + 1);
        mp[x]++;
        ans.pop_back();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }

    bt(0);

    cout << 0;

//     if (mp.count(P[1] * 8) && mp.count(P[2])) {
//         cout << 2 << '\n';
//         cout << P[1] * 8 << ' ' << P[2];
//         exit(0);
//     }
//     if (mp.count(P[1] * 4) && mp.count(P[2] * 2)) {
//         cout << 2 << '\n';
//         cout << P[1] * 4 << ' ' << P[2] * 2;
//         exit(0);
//     }
//     if (mp.count(P[1] * 2) && mp.count(P[2] * 4)) {
//         cout << 2 << '\n';
//         cout << P[1] * 2 << ' ' << P[2] * 4;
//         exit(0);
//     }
//     if (mp.count(P[1]) && mp.count(P[2] * 8)) {
//         cout << 2 << '\n';
//         cout << P[1] << ' ' << P[2] * 8;
//         exit(0);
//     }

//     if (mp.count(2) && mp.count(P[1]) && mp.count(P[2] * 4)) {
//         cout << 3 << '\n';
//         cout << 2 << ' ' << P[1] << ' ' << P[2] * 4;
//         exit(0);
//     }
//     if (mp.count(2) && mp.count(P[1] * 2) && mp.count(P[2] * 2)) {
//         cout << 3 << '\n';
//         cout << 2 << ' ' << P[1] * 2 << ' ' << P[2] * 2;
//         exit(0);
//     }
//     if (mp.count(2) && mp.count(P[1] * 4) && mp.count(P[2])) {
//         cout << 3 << '\n';
//         cout << 2 << ' ' << P[1] * 4 << ' ' << P[2];
//         exit(0);
//     }

//     if (mp[2] >= 2 || mp[4] >= 1) {
//         vector<int> res;
//         if (mp[2] >= 2) {
//             res.push_back(2);
//             res.push_back(2);
//         } else {
//             res.push_back(4);
//         }

//         if (mp.count(P[1] * 2) && mp.count(P[2])) {
//             res.push_back(P[1] * 2);
//             res.push_back(P[2]);
//             print(res);
//         }
//         if (mp.count(P[1]) && mp.count(P[2] * 2)) {
//             res.push_back(P[1]);
//             res.push_back(P[2] * 2);
//             print(res);
//         }
//     }

//     if (mp[2] >= 3 || (mp[2] >= 1 && mp[4] >= 1) || (mp[8] >= 1)) {
//         vector<int> res;
//         if (mp[2] >= 3) {
//             res.push_back(2);
//             res.push_back(2);
//             res.push_back(2);
//         } else if (mp[2] >= 2 && mp[4] >= 1) {
//             res.push_back(2);
//             res.push_back(4);
//         } else res.push_back(8);

//         if (mp.count(P[1]) && mp.count(P[2])) {
//             res.push_back(P[1]);
//             res.push_back(P[2]);
//             print(res);
//         }
//     }

//     cout << 0;
// }
}