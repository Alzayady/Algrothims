class Solution {
public:
    
    int getSize(ListNode * head){
      int ans = 0;
      while(head!=NULL){
        head = head->next;
        ans++;
      }
      return ans;
    }
    pair<ListNode * , ListNode *>split(ListNode* head){ // 1 4 5    6  12  7 
       int s = getSize(head);
       int firstSize = s /2;
       int secondSize = s - firstSize ;
       ListNode * firstListHead = head;
       ListNode * tail = head;
       while(--firstSize){
         tail = tail-> next ;
       }
       ListNode * secondListHead = tail->next;
       tail->next = NULL;
      return {firstListHead,secondListHead};
    }
  
    ListNode *merge(ListNode * a , ListNode * b){
      ListNode * cur  =NULL;
      ListNode * begin = NULL;
      while (a!=NULL and b!=NULL){
        if(a->val < b->val){
          if(cur == NULL){
            cur = a;
            begin = cur;
          }else{
            cur->next = a;
             cur = cur->next;
          }
          ListNode * temp = a;
          a = a->next;
          temp->next = NULL;
        }else{
           if(cur == NULL){
            cur = b;
            begin = cur;
          }else{
            cur->next = b;
              cur = cur->next;
          }
          ListNode * temp = b;
      
          b = b->next;
          temp->next =NULL;
          
        }
       
      }
      if(a!=NULL){
        cur->next = a;
      }
      if(b!=NULL){
        cur->next = b;
      }
      return begin;
    }
    ListNode* sortList(ListNode* head) {
       
      int s = getSize(head);
      if(s<=1){
        return head;
      }
       pair<ListNode * , ListNode *> lists = split(head);
       ListNode *a = sortList(lists.first);
       ListNode *b = sortList(lists.second);
       ListNode * temp =  merge(a, b);
      return temp;
    }
};
