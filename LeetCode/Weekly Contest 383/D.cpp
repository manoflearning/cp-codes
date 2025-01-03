#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXS = 101010;
string s;
int z[MAXS];

void zfunction() {
    z[0] = sz(s);
    int l = 0, r = 0;
    for (int i = 1; i < sz(s); i++) {
        if (i > r) {
            l = r = i;
            while (r < sz(s) && s[r - l] == s[r]) r++;
            z[i] = r - l; r--;
        }
        else {
            int k = i - l;
            if (z[k] < r - i + 1) z[i] = z[k];
            else {
                l = i;
                while (r < sz(s) && s[r - l] == s[r]) r++;
                z[i] = r - l; r--;
            }
        }
    }
}

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        s = word;
        // reverse(all(s));
        
        zfunction();
        
        int ret = (sz(word) + k - 1) / k;
        for (int i = k; i < sz(s); i += k) {
            if (z[i] >= sz(word) - i) { ret = i / k; break; }
        }
        return ret;
    }
};