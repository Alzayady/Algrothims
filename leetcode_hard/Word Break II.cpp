class Solution {
public:
    struct trie {
        trie *next[26];
        int lastIndex = -1;

        trie() {
            for (int i = 0; i < 26; i++) {
                next[i] = NULL;
            }
        }

        void insert(string &str, int index, int in) {
            if (index == str.size()) {
                lastIndex = in;
                return;
            }
            if (!next[str[index] - 'a']) next[str[index] - 'a'] = new trie();
            next[str[index] - 'a']->insert(str, index + 1, in);
        }

        int match(string &str, int index) {
            if (index == str.size())return lastIndex;
            if (next[str[index] - 'a'] == NULL)return -1;
            return next[str[index] - 'a']->match(str, index + 1);
        }
    };

    vector <vector<int>> next;
    vector <string> words;
    vector <vector<string>> dp;
    vector<bool> solvedDp;

    vector <string> solve(int index, string &str) {
        if (index == str.size()) {
            return {""};
        }
        if (index > str.size()) {
            return {};
        }
        if (solvedDp[index]) {
            return dp[index];
        }
        solvedDp[index] = 1;
        vector <string> ans;
        for (int nx: next[index]) {
            int nextIndex = index + words[nx].size() ;
            vector <string> s = solve(nextIndex, str);
            for (string it: s) {
                if(it.size())
                ans.push_back(words[nx] + " " + it);
                else 
                ans.push_back(words[nx] );

            }
        }
        return dp[index]=ans;
    }


    vector <string> wordBreak(string s, vector <string> &wordDict) {
        words = wordDict;
        trie t = trie();
        int c = 0;
        for (string str: wordDict) {
            t.insert(str, 0, c++);
        }
        int n = s.size();
        next.resize(n);
        dp.resize(n);
        solvedDp.resize(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= 20; j++) {
                if (i + j > s.size())break;
                string te = s.substr(i, j);
                int index = t.match(te, 0);
                if (index == -1)continue;
                next[i].push_back(index);
            }
        }

        return solve(0, s);

    }
};
