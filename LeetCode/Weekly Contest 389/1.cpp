class Solution {
public:
    bool isSubstringPresent(string s) {
        set<pair<char, char>> st;
        for (int i = 0; i + 1 < s.size(); i++) {
            st.insert({ s[i], s[i + 1] });
        }
        for (int i = 0; i + 1 < s.size(); i++) {
            if (st.count({ s[i + 1], s[i] })) return true;
        }
        return false;
    }
};