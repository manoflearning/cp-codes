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

class Solution {
public:
    ll rop(const vector<ll>& p, int s, int e) {
        if (s > e) return 0;
        ll ret = 0;
        if (0 <= e && e < sz(p)) ret += p[e];
        if (0 <= s - 1 && s - 1 < sz(p)) ret -= p[s - 1];
        return ret;
    }
    ll rrop(const vector<ll>& p, int s, int e) {
        if (s > e) return 0;
        ll ret = 0;
        if (0 <= s && s < sz(p)) ret += p[s];
        if (0 <= e + 1 && e + 1 < sz(p)) ret -= p[e + 1];
        return ret;
    }
    ll minimumMoves(vector<int>& nums, int k, int maxChanges) {
        int n = sz(nums);
        
        // prefix sum
        vector<ll> ps(n), pm(n);
        ps[0] = nums[0];
        pm[0] = (nums[0] ? n - 1 : 0);
        for (int i = 1; i < n; i++) {
            ps[i] = nums[i] + ps[i - 1];
            pm[i] = (nums[i] ? n - i - 1 : 0) + pm[i - 1];
        }
        
        vector<ll> sm(n);
        sm[n - 1] = (nums[n - 1] ? n - 1 : 0);
        for (int i = n - 2; i >= 0; i--) {
            sm[i] = (nums[i] ? i : 0) + sm[i + 1];
        }
        
        // solve
        ll ret = 1e18;
        
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            ll res = 0;
            
            // case 1
            if (nums[i]) cnt++;
            if (cnt < k && (i > 0 && nums[i - 1])) cnt++, res++;
            if (cnt < k && (i + 1 < n && nums[i + 1])) cnt++, res++;
            
            // case 2
            {
                ll x = min(k - cnt, maxChanges);
                cnt += x, res += 2 * x;
            }
            
            // case 3
            if (cnt < k) {
                int l = 2, r = n - 1;
                while (l < r) {
                    int mid = (l + r) >> 1;

                    int lb = max(0, i - mid);
                    int ub = min(n - 1, i + mid);

                    int rangeCnt = 0;
                    rangeCnt += rop(ps, lb, i - 2);
                    rangeCnt += rop(ps, i + 2, ub);

                    if (rangeCnt < k - cnt) l = mid + 1;
                    else r = mid;
                }
                
                int lb = max(0, i - l);
                int ub = min(n - 1, i + l);
                
                // [lb, i - 2]
                res += rop(pm, lb, i - 2);
                res -= rop(ps, lb, i - 2) * (n - i - 1);
                // [i + 2, ub]
                res += rrop(sm, i + 2, ub);
                res -= rop(ps, i + 2, ub) * i;
            }
            
            // modify ret
            ret = min(ret, res);
        }
        
        return ret;
    }
};