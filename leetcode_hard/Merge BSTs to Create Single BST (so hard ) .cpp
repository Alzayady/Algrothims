/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    struct BST{
        TreeNode * tree;
        int min_v ;
        int max_v ;
    };
    vector<BST * > vec;
    vector<bool>taken;
    unordered_map<int , int > root_to_index;
    unordered_set<int>leafs;
    bool is_leaf(TreeNode * node){
        return node->left == NULL and node->right == NULL;
    }
    bool valid(TreeNode * node , int min_v = INT_MIN , int max_v = INT_MAX){
        if(node==NULL)return true;
        if(is_leaf(node)){
            leafs.insert(node->val);
            return true;
        }
        if(node->val <= min_v or node->val >= max_v)return false;
        return valid(node->left,min_v,node->val) and valid(node->right,node->val,max_v);
    }
    int get_most_left(TreeNode * node){
        if(node->left ==NULL)return node->val;
        return get_most_left(node->left);
    }
    int get_most_right(TreeNode * node){
        if(node->right ==NULL)return node->val;
        return get_most_right(node->right);
    }
    pair<int , int >get_constrains(TreeNode * node){
        int left = get_most_left(node);
        int right= get_most_right(node);
        pair<int , int>ans ;
        ans.first = left;
        ans.second = right;
        return ans;
    }
    void dfs(int ind , TreeNode * node , int min_v = INT_MIN , int max_v = INT_MAX){
        if(node==NULL)return;
        if(is_leaf(node)){
             if(root_to_index.count(node->val)){
                 int index = root_to_index[node->val];
                                  if(!taken[index] and index != ind){
                     BST * t = vec[index];
                     if(t->min_v > min_v and t->max_v < max_v){
                         taken[index] = true;
                         node->left = t->tree->left;
                         node->right=t->tree->right;
                         dfs(ind,node,min_v,max_v);
                     }
                 }
             }
             return ;   
        }
        dfs(ind,node->left,min_v,node->val);
        dfs(ind,node->right,node->val,max_v);
    }
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        for(auto it : trees){
            if(!valid(it))return NULL;
        }
        int cur = 0 ;
        for(auto it : trees){
            pair<int , int> constrains = get_constrains(it);
            BST * t = new BST();
            t->min_v = constrains.first;
            t->max_v = constrains.second;
            t->tree = it;
            vec.push_back(t);
            root_to_index[it->val] = cur++;
        }
        int n = trees.size();
        taken.resize(n,0);
        for(int i = 0; i < n; i ++){
           if(!leafs.count(vec[i]->tree->val)){
                 dfs(i,vec[i]->tree);
                 break;
           }
           
        }
        int cnt = 0 ;
        TreeNode * ans ;
        for(int i = 0; i< n ; i++){
            if(!taken[i]){
                cnt++;
                ans = vec[i]->tree;
            }
            if(cnt>1)return NULL;
        }
        if(!valid(ans))return NULL;
        return ans;
        
    }
};
