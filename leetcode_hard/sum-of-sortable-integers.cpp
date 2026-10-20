class Solution {
public:
    vector<int>sorted;
    bool can_solve(vector<int>& nums, int k) {
        // 4 + 2 + 1 
        int n = nums.size();
        for(int i = 0 ; i <n ; i += k) {
            // same elements 
            unordered_map<int, int> part ;
            for(int j = i ; j < i + k ; j ++) {
                part[nums[j]] ++;
                part[sorted[j]]--;
            }
            for(auto it : part) {
                if(it.second) return false;
            }
            int biggest_index = i ;
            bool turned = false;
            int should_be_smalled  = -1;
            bool same = true;
            for(int j = i ; j < i + k ; j ++) {
                int next = j + 1 ;
                
                if(next == i + k) {
                    next = i ;
                }
                if(nums[j] != nums[next]) same = false;
                if(nums[j] > nums[next]) {
                    if(turned) return false;
                    should_be_smalled = next;
                    turned = true;
                    // 1 2 10 5 
                }
            }
            if(same) continue;
            int start = should_be_smalled ;
            int shift = 1 ;
            while(shift < k) {
                shift ++;
                int next = start + 1 ;
                if(next == i + k) next = i ;
                if(nums[start] > nums[next]){
                 return false;
                }
                start++;
                if(start == i + k) start = i ;
            }
        }
        return true;
    }

    int sortableIntegers(vector<int>& nums) {
        sorted =nums;
        sort(sorted.begin() ,sorted.end());

        int ans = 0 ;       
        int n = nums.size(); 
        if(n == 1) return 1;
        for(int i = 1 ; i * i <=n ; i ++) {
            if(n % i == 0 ) {
                if(can_solve(nums,i)) {
                    ans += i ; 
                }
                if( i == n / i) continue;
                if(can_solve(nums,n / i)) {
                    ans += n / i ; 
                }

            }
        }
        return ans;
    }
};
