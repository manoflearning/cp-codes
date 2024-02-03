// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
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
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int N;
vector<string> A;
map<string, ll> mp;
int dp[1010][1010];
string mx;

typedef unsigned int uint32;

enum PaddingType { LEFT, RIGHT };

///
/// Add a padding char n times to the left or the right of the string 
///
string padString(const string& toPad, size_t paddingCountToAdd, char paddingChar, PaddingType paddingType = RIGHT) { 
    string s(paddingCountToAdd, paddingChar);
    return paddingType == LEFT ? s + toPad : toPad + s;
}

///
/// Checks if the string is composed of only '0's 
/// 
bool isZero(const string& oper) {
    for (size_t i = 0, l = oper.size(); i < l; i++) 
        if (oper[i] != '0') return false;
    return true;
}

/// 
/// Given two strings, both representing numbers, returns a new string that represents the sum of them
/// 
string sumIntStrings(const string& op1, const string& op2) {
    if (op2 == "") return op1;
    if (op1 == "") return op2;
    string total = "";
    size_t op1Size = op1.size();
    size_t op2Size = op2.size();
    size_t m = max(op1Size, op2Size);

    uint32 carry = 0;
    for (int i = 0; i < static_cast<int>(m); i++) {
        uint32 c0 = i < op1Size ? op1[op1Size - 1 - i] - '0' : 0;
        uint32 c1 = i < op2Size ? op2[op2Size - 1 - i] - '0' : 0;
        uint32 c = c0 + c1 + carry;
        carry = c / 10;
        total += (c % 10) + '0';
    }
    if (carry) total += carry + '0';
    reverse(total.begin(), total.end());
    return total;
}

///
/// Removes the zeros from the left of the number
/// 
string removeLeftZeros(const string& value) {
    // Delete '0's from the left
    if (value.size() > 1 && value[0] == '0') {
        for (size_t i = 0, l = value.size(); i < l; i++) {
            if (value[i] == '0')
                continue;
            return value.substr(i, l - i);
        }
    } 
    return value;
}

///
/// Given two strings, both representing numbers, returns a new string that represents the substraction 
/// of them, for that, it assumes that the first parameter is always great than or equal to the second parameter
/// 
string subIntStrings(const string& op1, const string& op2) {
    if (op2 == "") return op1;

    string total = "";
    size_t op1Size = op1.size();
    size_t op2Size = op2.size();

    uint32 carry = 0;
    for (int i = 0; i < op1Size; i++) {
        int c0 = op1[op1Size - 1 - i] - '0' - carry;
        int c1 = i < op2Size ? op2[op2Size - 1 - i] - '0' : 0;
        carry = 0;
        if (c0 < c1) {
            carry = 1;
            c0 += 10;
        }
        total += (c0 - c1) + '0';
    }
    reverse(total.begin(), total.end());
    return isZero(total) ? "0" : removeLeftZeros(total);
}

///
/// Returns a string that represents the product of the first parameter by the 
/// digit that second parameter represents 
/// 
string mulIntStringByChar(const string& op1, const char op2) {
    if (op2 == '0') return "0";
    if (op2 == '1') return op1;

    int carry = 0;
    int d0 = op2 - '0';
    string r = "";
    for (int j = op1.size() - 1; j >= 0; j--) {
        int d1 = op1[j] - '0';
        int d = (d0 * d1) + carry;
        carry = d / 10;
        d %= 10;
        r += d + '0';
    }
    if (carry) r += carry + '0';
    reverse(r.begin(), r.end());
    return r;
}

///
/// Performs the 3th grade multiplication over the two parameter strings 
/// (both representing numbers)
/// 
string mulThirdGrade(const string& op1, const string& op2) {
    list<string> res;
    uint32 padding = 0;
    // O(n ^ 2)
    for (int i = op2.size() - 1; i >= 0; i--) {
        res.push_back(padString(mulIntStringByChar(op1, op2[i]), padding, '0', RIGHT));
        padding++;
    }

    // O(n ^ 2)
    string total = "";
    for (string line : res)
        total = sumIntStrings(total, line);
    return total;
}

///
/// Performs the karatsuba multiplication over the two parameter strings 
/// (both representing numbers)
///
string multKaratsuba(string op1, string op2) { 
    // O(1) (theoritically)
    size_t l1 = op1.size();
    size_t l2 = op2.size();

    if (l1 == 1 || l2 == 1)
        // O(1)
        return mulIntStringByChar(l1 == 1 ? op2 : op1, l1 == 1 ? op1[0] : op2[0]);

    // Divide
    size_t n = max(l1, l2);
    n += (n & 1);

    // 2 * O(n)
    op1 = padString(op1, n - l1, '0', LEFT);
    op2 = padString(op2, n - l2, '0', LEFT);

    size_t n2 = n / 2;

    // 4 * O(n)
    string a = op1.substr(0, n2);
    string b = op1.substr(n2, n2);
    string c = op2.substr(0, n2);
    string d = op2.substr(n2, n2);

    // 2 recursive calls
    string ac = multKaratsuba(a, c);
    string bd = multKaratsuba(b, d);

    // 2 * O(n)        
    string _ab = sumIntStrings(a, b);
    string _cd = sumIntStrings(c, d);

    // another call
    string abcd = multKaratsuba(_ab, _cd);

    // 2 * O(n)
    abcd = subIntStrings(abcd, ac);
    abcd = subIntStrings(abcd, bd);

    // 5 * O(n)
    ac = padString(ac, n, '0', RIGHT);
    abcd = padString(abcd, n2, '0', RIGHT);
    string res = sumIntStrings(ac, abcd);
    res = sumIntStrings(res, bd);
    return removeLeftZeros(res);
}

bool cmp(const string& p1, const string& p2) {
    if (sz(p1) != sz(p2)) return sz(p1) < sz(p2);
    for (int i = 0; i < sz(p1); i++) {
        if (p1[i] != p2[i]) return p1[i] < p2[i];
    }
    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        mp[A[i]]++;
        // if (cmp(mx, A[i])) mx = A[i];
    }

    // sort(all(A), cmp);
    // A.erase(unique(all(A)), A.end());

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        // if (i > 0 && A[i] == A[i - 1]) continue;
        for (int j = i; j < N; j++) {
            // if (j > i && A[j] == A[j - 1]) continue;
            string res = multKaratsuba(A[i], A[j]);
            // if (cmp(mx, res)) break;
            if (!mp.count(res)) continue;
            ans += mp[res] * (i != j ? 2 : 1);
        }
    }

    cout << ans;
}