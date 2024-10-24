#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define ll long long

const int UB = 180'000;

ll p3[22], p5[22];

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    p3[0] = p5[0] = 1;
    for(int i = 0; i + 1 < 22; i++){
        p3[i + 1] = p3[i] * 3;
        if (p3[i + 1] > UB) break;
    }
    for(int i = 0; i + 1 < 22; i++){
        p5[i + 1] = p5[i] * 5;
        if (p5[i + 1] > UB) break;
    }

    vector<int> ans;
    for (int c = 1; c <= UB; c++) {
        if (c % 3 == 0 || c % 5 == 0) continue;

        for (int x = 0; p3[x] != 0; x += 3) {
            for (int y = 0; p5[y] != 0; y += 3) {
                for (int t = 0;  p3[x + t] != 0 && p5[y + t] != 0; t++) {
                    ll res = c * p3[x + t] * p5[y + t];
                    if (res <= UB) ans.push_back(res);
                }
            }
        }
    }

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());

    int tc; cin >> tc;
    for(int i = 0; i < tc; i++){
        int tmp; cin >> tmp;
        cout << ans[tmp - 1] << '\n';
    }
}
