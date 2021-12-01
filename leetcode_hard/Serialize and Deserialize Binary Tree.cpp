/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    const char SPACE = ',';
    const char EMPTY = 'X';
    int get_height(TreeNode * root){
        if(root==NULL)return 0;
        return 1 + max(get_height(root->left) , get_height(root->right));
    }
    string intToString(int num){
        bool neg = num < 0 ;
        num = abs(num);
        if(num == 0){
            return "0";
        }
        string ans ;
        while(num){
            ans+= '0' + num%10;
            num/=10;
        }
        reverse(ans.begin(),ans.end());
        if(neg){
            return "-" + ans;
        }
        return ans;
    }
    int stringToInt(string str){
        if(str[0]=='-'){
            return -1 * stringToInt(str.substr(1));
        }
        int ans = 0;
        for(char c : str){
            ans*=10;
            ans+=c - '0';
        }
        return ans;
    }
    string serialize(TreeNode* root) {
        int height = get_height(root);
        string ans = intToString(height);
        queue<TreeNode * > bfs;
        bfs.push(root);
        while(height --){ 
            int s =  bfs.size();
            while(s--){
                TreeNode * cur = bfs.front();
                bfs.pop();
                ans+=SPACE;
                if(cur==NULL){
                    ans+=EMPTY;
                }else{
                    ans+= intToString(cur->val);
                    bfs.push(cur->left);
                    bfs.push(cur->right);
                }
            }
        }
        return ans;
    }

    vector<string> split(string data){
        vector<string> ans ;
        string last ;
        int n = data.size();
        for(int i = 0; i < n ; i++){
            if(data[i] ==SPACE){
                ans.push_back(last);
                last = "";
            }else{
                last += data[i];
            }
        }
        assert(last.size()!=0);
        ans.push_back(last);
        return ans;
    }
    TreeNode * get_node(string str){
        if(str[0] == EMPTY){
            return NULL;
        }
        return new TreeNode(stringToInt(str));
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> parts = split(data);
        int height = stringToInt(parts[0]);
        if(height == 0){
            return NULL;
        }
        TreeNode * ans = new TreeNode(stringToInt(parts[1]));
        vector<TreeNode *>  lastLevel ;
        lastLevel.push_back(ans);
        int node = 2 ;
        while(--height){
            vector<TreeNode *>cur_level ;
            for(auto it : lastLevel){
                if(it != NULL){
                    TreeNode * left = get_node(parts[node++]);
                    cur_level.push_back(left);
                    TreeNode * right = get_node(parts[node++]);
                    cur_level.push_back(right);
                    it->left = left;
                    it->right = right;
                }
            }
            lastLevel = cur_level;
        }
        return ans;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
