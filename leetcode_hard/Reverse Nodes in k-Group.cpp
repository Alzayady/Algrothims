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
    struct buffer{
        ListNode * firstNode ;
        ListNode * lastNode ;
        ListNode * firstNextGroup;
    };
    int get_size(ListNode *t){
        int ans = 0; 
        while(t!=NULL){
            ans++;
            t = t->next;
        }
        return ans;
    }
    buffer * rev(ListNode * node , int k ){
        buffer * b = new buffer();
        ListNode * first = node ;
        ListNode * second = node->next;
        first->next = NULL;
        b->lastNode = node;
        while(--k){
            ListNode * temp = second->next;
            second->next = first;
            first = second;
            second = temp;
        }
      
        b->firstNextGroup = second;
        b->firstNode = first;
        return b;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        int sz = get_size(head);
        int r = sz / k ;
        ListNode * ans =NULL ;
        ListNode * lastprev = NULL;
        while(r--){
            buffer * b = rev(head,k);
            if(ans == NULL){
                ans = b->firstNode;
            }else{
                lastprev->next = b->firstNode;
            }
            lastprev = b->lastNode;
            head = b->firstNextGroup;
            
        }
        lastprev->next = head;
        return ans;
    }
};
