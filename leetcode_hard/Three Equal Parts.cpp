class Solution {
public:
    
    bool same(int l1, int r1, int l2, int r2, vector<int> &vec) {
        while (vec[l1] == 0 and l1<r1) {
            l1++;
        }
        while (vec[l2] == 0 and l2<r2) {
            l2++;
        }
        while (l1 <= r1 and l2 <= r2) {
            if (vec[l1] != vec[l2])return false;
            l1++;
            l2++;
        }
        if (l1 != r1 +1 or l2 != r2 +1 )return false;
        return true;
    }

    vector<int> threeEqualParts(vector<int> arr) {
        int n = arr.size();
        int o = 0;
        for (int i : arr) {
            o += i;
        }
        if (o % 3) {
            return {-1, -1};
        }
        if(o==0){
            return {0,2};
        }
        o /= 3;
        int l = 0;
        int c_o = 0;

        while (c_o < o) {
            c_o += arr[l];
            l++;
        }
        int r = n - 1;
        c_o = 0;
        int end_z = 0;
        while (c_o < o) {
            c_o += arr[r];
            r--;
            if (c_o == 0) {
                end_z++;
            }
        }
        int temp_end = end_z;
        while (end_z--) {
            if (arr[l])return {-1, -1};
            l++;
        }
        int z = 0;
        for (int i = r;; i--) {
            if (arr[i]) {
                break;
            }
            z++;
        }
        int shift = z - temp_end;
        if (shift < 0)return {-1, -1};
        r -= shift;
        if (same(0, l - 1, l, r, arr) and same(l, r, r + 1, n - 1, arr)) {
            return {l - 1, r + 1};
        }
        return {-1, -1};

    }
};
