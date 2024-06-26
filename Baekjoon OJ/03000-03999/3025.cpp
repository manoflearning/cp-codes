#include <bits/stdc++.h>
using namespace std;
#define fr first
#define sc second
#define pii pair<int, int>

int r, c, n;
vector<pii> dp[33];
map<int, char> mp[33];
string arr[303030];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        cin >> arr[i];
        for (int j = 0; j < c; j++) {
            if (arr[i][j] == 'X') 
                mp[j].insert({ i, 'X' });
        }
    }

    for (int i = 0; i < c; i++) {
        arr[r].push_back('X');
        mp[i].insert({ r, 'X' });
    }

    cin >> n;
    while (n--) {
        int st; cin >> st;
        st--;

        int y = -1, x = st;
        while (!dp[st].empty()) {
            int yy = dp[st].back().fr, xx = dp[st].back().sc;
            if (yy >= 0 && arr[yy][xx] != '.') {
                dp[st].pop_back();
                continue;
            }
            y = yy, x = xx;
            break;
        }
        
        while (1) {
            auto it = mp[x].lower_bound(y);
            int ny = it->fr - 1;
            
            if (it->sc == 'X') {
                arr[ny][x] = 'O';
                mp[x].insert({ ny, 'O' });
                break;
            }
            if (it->sc == 'O') {
                if (0 < x && arr[ny][x - 1] == '.' && arr[ny + 1][x - 1] == '.') {
                    dp[st].push_back({ y, x });
                    x = x - 1;
                    y = ny + 1;
                    continue;
                }
                if (x + 1 < c && arr[ny][x + 1] == '.' && arr[ny + 1][x + 1] == '.') {
                    dp[st].push_back({ y, x });
                    x = x + 1;
                    y = ny + 1;
                    continue;
                }

                arr[ny][x] = 'O';
                mp[x].insert({ ny, 'O' });
                break;
            }
        }
    }

    for (int i = 0; i < r; i++) 
        cout << arr[i] << '\n';

    return 0;
}