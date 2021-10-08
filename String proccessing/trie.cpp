class Trie {
public:
    Trie * children[26];
    bool isEndOfWord ;
    Trie() {
 
        isEndOfWord = false;

        for (int i = 0; i < 26; i++)
            children[i] = NULL;

    }
    
    void insert(string word , int index = 0 ) {
        if(index == word.size()) isEndOfWord = true;
        else{
            if(! children[word[index]-'a'])  children[word[index]-'a'] = new Trie();
           children[word[index]-'a']->insert(word,index+1);
        }
    }
    
    bool search(string word,int index = 0 ) {
        if(index==word.size())return isEndOfWord;
        if(! children[word[index]-'a']) return 0 ;
        return  children[word[index]-'a']->search(word,index+1);
    }
    
    bool startsWith(string prefix,int index = 0 ) {
        if(index==prefix.size())return 1;
        if(! children[prefix[index]-'a']) return 0 ;
        return  children[prefix[index]-'a']->startsWith(prefix,index+1);
    }
};
