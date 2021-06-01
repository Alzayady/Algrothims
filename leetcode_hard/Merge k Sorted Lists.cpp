/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<pair<int , int> , vector<pair<int , int >> , greater<pair<int , int >>>pq;
        int n = lists.size();
        for(int i = 0; i < n; i ++){
            if(lists[i]==NULL)continue;
            pq.push({lists[i]->val,i});
        }
    
        ListNode * ans = NULL;
        ListNode * last_node_ans =NULL;
        while(pq.size()){
            pair<int , int> p = pq.top();
            pq.pop();
            if(ans == NULL){
                ans = lists[p.second];
                last_node_ans = lists[p.second];
            }else{
                last_node_ans->next = lists[p.second];
                last_node_ans = last_node_ans->next;
            }
            lists[p.second] =  lists[p.second]->next;
            if(lists[p.second]!=NULL){
                pq.push({lists[p.second]->val,p.second});
            }
            
        }
    
         return ans;
    }
};
