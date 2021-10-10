class Solution {
public:
    
    struct trie{
        trie * next[26];
        bool isEnd = false;
        trie(){
            for(int i = 0 ;i < 26 ; i ++){
                next[i] = NULL;
            }
        }
        void insert(string &str , int index){
            if(index==str.size()){
                isEnd = 1 ;
                return ;
            }
            if(! next[str[index]-'a']) next[str[index]-'a'] = new trie();
            next[str[index]-'a']->insert(str,index+1);
        }
        bool match(string & str , int index){
            if(index==str.size())return isEnd ;
            if(next[str[index]-'a']==NULL)return 0 ;
            return next[str[index]-'a']->match(str,index+1);
        }
    };
    
    
    bool wordBreak(string s, vector<string>& wordDict) {
        trie t = trie();
        for(string str : wordDict){
            t.insert(str,0);
        }
        int n = s.size();
        vector<vector<int>>next(n);
        for(int i = 0 ;i < n ; i ++){
            for(int j = 1 ; j <= 20 ; j ++){
                if(i + j > s.size())break;
                string te = s.substr(i,j);
                if(t.match(te,0)){
                    next[i].push_back(i+j);
                }
            }
        }
        vector<bool>vis(n+1,0);
        vis[0] = 1 ;
        for(int i = 0; i < n ; i ++){
            if(vis[i]){
                for(int nx : next[i]){
                    vis[nx] = 1 ;
                }
            }
        }
        return vis[n];
    }
};
