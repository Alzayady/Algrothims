class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        int n =a.size();
        int m =b.size();
        if(n>m){
            swap(a,b);
            swap(n,m);
        }
        int s = (n+m)/2 ;
        int l = 0 , r = min(s,n) ;
        auto getLastA=[&](int num){
                        if(num==-1)return -1;
            if(num >=n)return INT_MAX;
            return a[num];
        }; 
        auto getLastB=[&](int num){
            if(num==-1)return -1;
            if(num >=m)return INT_MAX;
            return b[num];
        };
        
        auto getResult=[&](int num){
          int rem = s - num ;
          int lastA = getLastA(num-1);
          int lastB = getLastB(rem-1);
          int nextA = getLastA(num);
          int nextB = getLastB(rem);
          int last = max(lastA,lastB);
          int next = min(nextA, nextB);
          if(next >= last)return 0;
          if(next ==nextA){
              return 1;
          }
          return 2;
        };
        while(l<=r){
            int mid = (l+r)/2;
            int re = getResult(mid);
            if(re ==0){
                l = mid;
                break;
            }else if(re == 1 ){
                l = mid + 1;
            }else{
                r = mid - 1 ;
            }
        }
        if((n+m)%2==1){
            return min(getLastA(l),getLastB(s-l));
        }
         return (1.0* max(getLastA(l-1),getLastB(s-l-1)) +1.0*min(getLastA(l),getLastB(s-l)))/2.0;
    }
};
