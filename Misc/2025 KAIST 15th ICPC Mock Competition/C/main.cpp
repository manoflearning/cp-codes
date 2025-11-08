#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int dx[] = {1, -1, 0, 0};
constexpr int dy[] = {0, 0, 1, -1};

void query(const vector<int> &a) {
    cout << "? ";
    for (auto &i : a) cout << i << ' ';
    cout << '\n' << flush;
}
void answer(const vector<pii> &e) {
    cout << "! " << sz(e) << '\n';
    for (auto &i : e) {
        cout << i.fr << ' ' << i.sc << '\n';
    }
    cout << flush;
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
    // #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        
        vector<int> arr(n), brr(n), af(n);
        vector<pii> ans;

        ll sum=0;

        for(int i=0; i<n-1; i++) {
            for(int j=0; j<n; j++) {
                arr[j]=(i+j)%n+1;
            }

            query(arr);

            for(auto &b:brr) {
                cin >> b;
            }

            if(sum==0) for(auto &b:brr) sum+=b;
    
            if(i) {
                for(int j=1; j<n-i+1; j++) {
                    for(int k=0; k<brr[j-1]-af[j]; k++) {
                        ans.push_back({i, i+j});
                    }
                }
            }
            
            af=brr;

            // for(auto &[l,r]:ans) cout << l << ' ' << r << '\n';
        }
        while(sz(ans)<sum) {
            ans.push_back({n-1, n});
        }

        answer(ans);
    }
}
