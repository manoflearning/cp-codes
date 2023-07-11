// 2^a * 3^b 꼴의 홀수는 총 20개다. (a = 0일 때)
// 홀수는 최대 1번 사용 가능하다. a가 단조 증가해야 하기 때문이다.
// 
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int ub2 = 33, ub3 = 20;

ll n;
ll p2[ub2], p3[ub3];
map<ll, pair<int, int>> dp;

void init() {
    p2[0] = 1;
    for (int i = 1; i < ub2; i++) {
        p2[i] = 2 * p2[i - 1];
    }
    p3[0] = 1;
    for (int i = 1; i < ub3; i++) {
        p3[i] = 3 * p3[i - 1];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    vector<ll> arr;
    for (int i = 0; i < ub2; i++) {
        for (int j = 0; j < ub3; j++) {
            arr.push_back(p2[i] * p3[j]);
        }
    }
    sort(arr.begin(), arr.end());
    
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;

        vector<pair<int, int>> ans;
        int jmx = ub3 - 1;
        for (int i = 0; i < ub2; i++) {
            if (n < p2[i]) continue;
            if (!(n & p2[i])) continue;
            
            int j = 0;
            for (j = 0; j < jmx; j++) {
                if (n < p2[i] * p3[j]) break;
            }
            j--;

            n -= p2[i] * p3[j];
            ans.push_back({ i, j });
            jmx = j;
        }

        cout << ans.size() << '\n';
        for (auto& i : ans)
            cout << i.first << ' ' << i.second << '\n';
    }
}