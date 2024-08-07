#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

class Solution {
    vector<vector<int>> ps1;
    vector<vector<int>> ps2;
    vector<int> psame;
public:
    inline int sum1(int i, int lb, int ub) { return ps1[i][ub + 1] - ps1[i][lb]; }
    inline int sum2(int i, int lb, int ub) { return ps2[i][ub + 1] - ps2[i][lb]; }
    bool pcheck(int lb, int ub) {
        for (int i = 0; i < 26; i++) {
            if (sum1(i, lb, ub) != sum2(i, lb, ub)) return false;
        }
        return true;
    }
    bool isSame(int lb, int ub) { return (psame[ub + 1] - psame[lb] == ub - lb + 1); }
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int n = sz(s);
        
        string s1, s2;
        for (int i = 0; i < n / 2; i++) {
            s1.push_back(s[i]);
            s2.push_back(s[n - i - 1]);
        }
        
        //
        ps1.resize(26, vector<int>(n / 2 + 1));
        ps2.resize(26, vector<int>(n / 2 + 1));
        psame.resize(n / 2 + 1);
        for (int i = 0; i < n / 2; i++) {
            ps1[s1[i] - 'a'][i + 1]++;
            ps2[s2[i] - 'a'][i + 1]++;
            psame[i + 1] = (s1[i] == s2[i]) + psame[i];

            for (int j = 0; j < 26; j++) {
                ps1[j][i + 1] += ps1[j][i];
                ps2[j][i + 1] += ps2[j][i];
            }
        }
        
        //
        vector<bool> ret;
        for (auto& qu : queries) {
            int a = qu[0], b = qu[1];
            int c = n - qu[3] - 1, d = n - qu[2] - 1;
            bool res = true, isSwaped = false;
            
            if (a > c) { // wlog, a <= c
                swap(a, c);
                swap(b, d);
                isSwaped = true;
            }
            
            int lb = min(a, c), ub = max(b, d);
            
            res &= isSame(0, lb - 1);
            res &= isSame(ub + 1, n / 2 - 1);
            
            if (b < c) {
                res &= pcheck(a, b);
                res &= pcheck(c, d);
                res &= isSame(b + 1, c - 1);
            }
            else if (a <= c && d <= b) {
                res &= pcheck(a, b);    
            }
            else {
                if (isSwaped) {
                    swap(a, c);
                    swap(b, d);
                }
                
                vector<int> tmp1(26), tmp2(26);
                
                if (a <= c) {
                    for (int i = 0; i < 26; i++) {
                        tmp1[i] = sum1(i, a, b) - sum2(i, a, c - 1);
                        tmp2[i] = sum2(i, c, d) - sum1(i, b + 1, d);
                    }
                }
                else {
                    for (int i = 0; i < 26; i++) {
                        tmp1[i] = sum1(i, a, b) - sum2(i, d + 1, b);
                        tmp2[i] = sum2(i, c, d) - sum1(i, c, a - 1);
                    }
                }
                
                for (int i = 0; i < 26; i++) {
                    if (tmp1[i] < 0 || tmp2[i] < 0) res = false;
                    if (tmp1[i] != tmp2[i]) res = false;
                }
            }
            
            ret.push_back(res);
        }
        
        return ret;
    }
};